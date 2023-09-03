// Analyzer.cpp
#include "Analyzer.h"

Analyzer::Analyzer(std::string sfpath, std::string ofpath) : ofp(ofpath)
{
    loadMapFile(sfpath, map);
    mapToInsights(map);
}

Analyzer::Analyzer(std::map<std::string, std::vector<Record>> &smap, std::string ofpath) : ofp(ofpath)
{
    mapToInsights(smap);
}

Analyzer::~Analyzer()
{
}

void Analyzer::mapToInsights(std::map<std::string, std::vector<Record>> &smap)
{
    for (auto &[process, record_vec] : smap)
        add(process, record_vec);
}

long Analyzer::getRange(std::string start, std::string stop)
{
    // Split the timestamps into their components.
    std::string digits;
    std::vector<long> start_components;
    std::stringstream sstart(start);
    while (std::getline(sstart, digits, ':'))
    {
        start_components.push_back(std::stoi(digits));
    }

    std::vector<long> stop_components;
    std::stringstream sstop(stop);
    while (std::getline(sstop, digits, ':'))
    {
        start_components.push_back(std::stoi(digits));
    }

    // Calculate the difference between the timestamps.
    long hours = stop_components[0] - start_components[0];
    long minutes = stop_components[1] - start_components[1];
    long seconds = stop_components[2] - start_components[2];
    long milliseconds = stop_components[3] - start_components[3];

    long res = 0;
    res = HOURS_IN_MILLISECONDS * hours + MINUTES_IN_MILLISECONDS * minutes + SECONDS_IN_MILLISECONDS * seconds + milliseconds;

    return res;
}

std::string Analyzer::MillisecondsToString(long milliseconds)
{
    // Get the hours, minutes, seconds, and milliseconds from the milliseconds.
    long hours = milliseconds / (60 * 60 * 1000);
    long minutes = (milliseconds % (60 * 60 * 1000)) / (60 * 1000);
    long seconds = (milliseconds % (60 * 1000)) / 1000;
    long milliseconds_remainder = milliseconds % 1000;

    // Format the time as a string.
    std::string formatted_time = "";
    if (hours > 0)
    {
        formatted_time += std::to_string(hours) + ":";
    }
    if (minutes > 0)
    {
        formatted_time += std::to_string(minutes) + ":";
    }
    formatted_time += std::to_string(seconds) + "." + std::to_string(milliseconds_remainder);

    return formatted_time;
}

bool Analyzer::filter(std::string process)
{
    if (process.empty())
        return true;
    return false;
}

bool Analyzer::ValidateTimestamp(std::string timestamp)
{
    // Check the length of the string.
    int len = timestamp.length();
    if (len < 7 || len > 12)
    {
        return false;
    }

    // Check the characters in the string.
    for (int i = 0; i < len; i++)
    {
        if (timestamp[i] < '0' || timestamp[i] > '9' || timestamp[i] != ':')
        {
            return false;
        }
    }

    // The string is valid.
    return true;
}

std::tuple<std::string, long> Analyzer::analyze(std::vector<Record> records)
{
    std::vector<long> ranges;
    double medApproximation = 0.0;
    long medRange = 0;
    for (auto &r : records)
    {
        if (ValidateTimestamp(r.stop))
            ranges.push_back(getRange(r.start, r.stop));
        // else throw MyException("Process got no stop time, cannot calculate range");
    }
    if (ranges.empty())
        return {"REJECT", 0.0};

    for (auto &r : ranges)
    {
        medRange += r;
    }
    medRange = medRange / ranges.size();
    for (auto &r : ranges)
    {
        medApproximation += (std::abs(r / medRange));
    }
    medApproximation = medApproximation / ranges.size();
    if (medApproximation < apx)
        return {"ADD", medApproximation};
    else
        return {"REJECT", medApproximation};
}

void Analyzer::setApproximation(double approximation)
{
    apx = approximation;
}

void Analyzer::load()
{
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
    if (filter(process))
        return;
    std::tuple res = analyze(records);
    if (std::get<0>(res).compare("ADD") == 0)
    {
        insights[process].push_back(std::to_string(std::get<1>(res)));
    }
}

void Analyzer::toFile()
{
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