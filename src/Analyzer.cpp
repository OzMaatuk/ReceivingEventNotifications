// Analyzer.cpp
#include "Analyzer.h"

Analyzer::Analyzer(std::string sfpath, std::string ofpath) : ofp(ofpath)
{
    LOG(INFO) << "Creating Analyzer object from file";
    loadMapFile(sfpath, map);
}

Analyzer::Analyzer(std::map<std::string, std::vector<Record>> &smap, std::string ofpath) : ofp(ofpath), map(smap)
{
    LOG(INFO) << "Creating Analyzer object from map reference";
}

Analyzer::~Analyzer()
{
    LOG(INFO) << "Destructing Analyzer object";
}

void Analyzer::start()
{
    LOG(INFO) << "Start Analyzer";
    for (auto &[process, record_vec] : map)
        add(process, record_vec);
    toFile();
}

bool Analyzer::checkWhitelist(std::string process)
{
    if (process.empty())
        return true;
    if ((std::find(wl.begin(), wl.end(), process)) != wl.end())
        return true;
    return false;
}

std::tuple<bool, double> Analyzer::analyze(std::vector<Record> records)
{
    LOG(INFO) << "Analyze records for process";
    std::vector<long> durations;
    double medApproximation = 0.0;
    long medDuration = 0;

    for (auto &r : records)
    {
        if (isValidTimestamp(r.stop))
            durations.push_back(getRange(r.start, r.stop));
        else
            DLOG(WARNING) << "No valid stop time, cannot calculate range for process: "  + r.pid;
    }
    if (durations.empty())
        return {false, 0.0};

    for (auto &r : durations)
        medDuration += r;
    medDuration /= durations.size();

    for (auto &r : durations)
        medApproximation += (r / medDuration);
    medApproximation /= durations.size();

    if (medApproximation < apx)
        return {true, medApproximation};
    else
        return {false, medApproximation};
}

void Analyzer::setConfig(Config c)
{
    LOG(INFO) << "Set config";
    setApproximation(c.approximation);
    setWhitelist(c.white_list);
}

void Analyzer::setApproximation(double approximation)
{
    apx = approximation;
}

void Analyzer::setWhitelist(std::vector<std::string> white_list)
{
    wl = white_list;
}

void Analyzer::load()
{
    LOG(INFO) << "Loading process map from file " << ofp;
    // Create the JSON object.
    Json::Value root;
    // Read the JSON file into the JSON object.
    std::ifstream fin(ofp);
    if (fin.is_open())
    {
        Json::Reader reader;
        reader.parse(fin, root);
        fin.close();
    }
    else
    {
        LOG(WARNING) << "Could not load application data file " << ofp;
        return;
    }

    // Iterate over the objects in the JSON object.
    for (auto it = root.begin(); it != root.end(); it++)
    {
        // Get the pid.
        std::string process = it.name();

        // Create a vector to store the records for the pid.
        std::vector<std::string> pinisights;

        Json::Value earray = root[process];
        // Iterate over the elements in the object.
        for (auto e = earray.begin(); e != earray.end(); e++)
        {
            // Get current value from array
            Json::Value current = earray[e.index()];
            // Add the record to the vector.
            pinisights.push_back(current.asString());
        }

        // Add the vector to the map.
        insights[process] = pinisights;
    }
}

void Analyzer::add(std::string process, std::vector<Record> records)
{
    DLOG(INFO) << "Adding record for process " << process;
    if (checkWhitelist(process))
        return;
    std::tuple res = analyze(records);
    bool key = std::get<bool>(res);
    double value = std::get<double>(res);

    if (key)
    {
        std::string description = "All executions durations are similar with approximation: ";
        value *= 100;
        description += std::to_string(value) + "%";
        insights[process].push_back(description);
    }
}

void Analyzer::toFile()
{
    LOG(INFO) << "Creating Insights file";
    std::ofstream ofile(ofp);
    // Create a JSON object to store the map.
    Json::Value root = Json::objectValue;
    for (auto it = insights.begin(); it != insights.end(); ++it)
    {
        Json::Value process = Json::arrayValue;
        for (auto obj = it->second.begin(); obj != it->second.end(); ++obj)
        {
            process.append(obj->c_str());
        }
        root[it->first] = process;
    }
    // Write the JSON object to a file.
    ofile << root.toStyledString();
    ofile.flush();
    ofile.close();
}