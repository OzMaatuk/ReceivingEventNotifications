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

bool Analyzer::checkWhitelist(const std::string& process) const
{
    if (!process.empty() && (std::find(wl.begin(), wl.end(), process)) != wl.end())
        return true;
    return false;
}

const std::string Analyzer::isMaliciousTiming(const std::list<Record>& records) const
{
    VLOG(1) << "Start isMaliciousTiming";
    std::vector<long> durations;
    double medApproximation = 0.0;
    long medDuration = 0;

    // TODO: something wrong, not all process are added.

    for (auto &r : records)
    {
        VLOG(1) << r.pid;
        if (isValidTimestamp(r.stop))
            durations.push_back(getRange(r.start, r.stop));
        else
            VLOG(1) << "No valid stop time, cannot calculate range for process: "  + r.pid;
    }

    for (auto &r : durations)
        medDuration += r;
    if (durations.size() > 0)
        medDuration /= durations.size();

    for (auto &r : durations)
        medApproximation += (r / medDuration);
    if (durations.size() > 0)
        medApproximation /= durations.size();

    VLOG(1) << "Done isMaliciousTiming";

    if (medApproximation >= timingApx)
    {
        std::string description = "All executions durations are similar with approximation: ";
        double value = medApproximation * 100;
        description += std::to_string(value) + "%";
        return description;
    }
    return "";
}

std::map<std::string, std::string> Analyzer::analyze(const std::list<Record>& records)
{
    VLOG(1) << "Analyze records for pids:";
    std::map<std::string, std::string> res = std::map<std::string, std::string>();
    std::string tmp = isMaliciousTiming(records);
    if (!tmp.empty()) res.insert_or_assign("TIMING_ALERT", tmp);
    return res;
}

void Analyzer::setConfig(const Config& c)
{
    LOG(INFO) << "Set config";
    setTimingApproximation(c.approximation);
    setWhitelist(c.white_list);
}

void Analyzer::setTimingApproximation(double approximation)
{
    timingApx = approximation;
}

void Analyzer::setWhitelist(const std::list<std::string>& white_list)
{
    wl = std::list<std::string>(white_list.begin(), white_list.end()); // Deep copy
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
            // Add the record to the list.
            pinisights.insert_or_assign(e, current[e].asCString());
        }
        
        // Add the list to the map.
        insights[process] = pinisights;
    }
}

void Analyzer::add(const std::string& process, const std::list<Record>& records)
{
    VLOG(1) << "Adding record for process " << process;
    if (checkWhitelist(process))
        return;
    insights[process] = analyze(records); // TODO: Make it add new insights and not overwrite all.
}

void Analyzer::start(const std::map<std::string, std::list<Record>>& map)
{
    LOG(INFO) << "Start Analyzer";
    for (auto &[process, record_vec] : map)
        add(process, record_vec);
    toFile();
}

void Analyzer::toFile() const
{
    LOG(INFO) << "Creating Insights file";
    // Create a JSON object to store the map.
    Json::Value root = Json::objectValue;
    for (const auto& [key, inner_map] : insights)
    {
        Json::Value processInsights = Json::objectValue;

        for (const auto& [inner_key, inner_value] : inner_map)
            processInsights[inner_key] = inner_value;

        root[key] = processInsights;
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