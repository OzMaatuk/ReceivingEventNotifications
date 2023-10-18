// Analyzer.cpp
#include "Analyzer.h"

Analyzer::Analyzer(const std::string& ofp)
 : outputFilePath(ofp), insights()
{
    LOG(INFO) << "Creating Analyzer object from file";
    load(outputFilePath);
}

Analyzer::Analyzer(const Config& c) : Analyzer(c.insights_file_path)
{
    setConfig(c);
}

Analyzer::~Analyzer()
{
    LOG(INFO) << "Destructing Analyzer object";
}

bool Analyzer::checkWhitelist(const std::string& process)
{
    if (!process.empty() && (std::find(wl.begin(), wl.end(), process)) != wl.end())
        return true;
    return false;
}

std::tuple<bool, double> Analyzer::analyze(const std::vector<Record>& records)
{
    LOG(INFO) << "Analyze records for pid:";
    std::vector<long> durations;
    double medApproximation = 0.0;
    long medDuration = 0;

    // TODO: something wrong, not all process are added.

    for (auto &r : records)
    {
        DLOG(INFO) << r.pid;
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

void Analyzer::setConfig(const Config& c)
{
    LOG(INFO) << "Set config";
    setApproximation(c.approximation);
    setWhitelist(c.white_list);
}

void Analyzer::setApproximation(double approximation)
{
    apx = approximation;
}

void Analyzer::setWhitelist(const std::vector<std::string>& white_list)
{
    wl = std::vector<std::string>(white_list.begin(), white_list.end()); // Deep copy
}

void Analyzer::load(const std::string& ofp)
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

        // Create a map to store the records for the pid.
        std::map<std::string, std::string> pinisights;

        Json::Value current = root[process];
        // Iterate over the elements in the object.
        for (auto e : current.getMemberNames())
        {
            // Add the record to the vector.
            pinisights.insert_or_assign(e, current[e].asCString());
        }
        
        // Add the vector to the map.
        insights[process] = pinisights;
    }
}

void Analyzer::add(const std::string& process, const std::vector<Record>& records)
{
    DLOG(INFO) << "Adding record for process " << process;
    if (checkWhitelist(process)) // TODO: Not working.
        return;
    std::tuple res = analyze(records);
    bool key = std::get<bool>(res);
    double value = std::get<double>(res);

    if (key)
    {
        std::string description = "All executions durations are similar with approximation: ";
        value *= 100;
        description += std::to_string(value) + "%";
        insights[process].insert_or_assign("ALERT1", description);
    }
}

void Analyzer::start(const std::map<std::string, std::vector<Record>>& map)
{
    LOG(INFO) << "Start Analyzer";
    for (auto &[process, record_vec] : map)
        add(process, record_vec);
    toFile();
}

void Analyzer::toFile()
{
    LOG(INFO) << "Creating Insights file";
    // Create a JSON object to store the map.
    Json::Value root = Json::objectValue;
    for (auto it = insights.begin(); it != insights.end(); ++it)
    {
        Json::Value processAlerts = Json::objectValue;
        for (auto p = it->second.begin(); p != it->second.end(); ++p)
        {
            processAlerts[p->first].append(Json::Value(p->second));
        }
        root[it->first] = processAlerts;
    }
    // Write the JSON object to a file.
    std::ofstream ofile(outputFilePath);
    ofile << root.toStyledString();
    ofile.flush();
    ofile.close();
}

std::map<std::string, std::map<std::string, std::string>>& Analyzer::getInsights()
{
    return insights;
}