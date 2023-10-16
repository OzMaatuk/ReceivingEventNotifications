// Commons.h
#ifndef COMMONS_H
#define COMMONS_H

#include <glog/logging.h>
#include <json/json.h>
#include <json/writer.h>
#include <fstream>
#include <vector>
#include <map>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <regex>
#include "Config.h"
#include "Record.h"
#include "MyException.h"

inline static void printRecordsMap(std::map<std::string, std::vector<Record>> &map)
{
    for (auto it = map.begin(); it != map.end(); ++it)
    {
        printf("ProcessName: %s\n", it->first.c_str());
        for (auto obj = it->second.begin(); obj != it->second.end(); ++obj)
        {
            printf("  PID: %s\n", obj->pid.c_str());
            printf("  Start: %s\n", obj->start.c_str());
            printf("  Stop: %s\n", obj->stop.c_str());
        }
    }
}

inline static void loadMapFile(std::string sfp, std::map<std::string, std::vector<Record>> &map)
{
    // Create the JSON object.
    Json::Value root;
    // Read the JSON file into the JSON object.
    std::ifstream fin(sfp);
    if (fin.is_open())
    {
        Json::Reader reader;
        reader.parse(fin, root);
        fin.close();
    }
    else
    {
        LOG(WARNING) << "Could not load application data file " << sfp;
        return;
    }

    // Iterate over the objects in the JSON object.
    for (auto it = root.begin(); it != root.end(); it++)
    {
        // Get the pid.
        std::string process = it.name();

        // Create a vector to store the records for the pid.
        std::vector<Record> records;

        Json::Value earray = root[process];
        // Iterate over the elements in the object.
        for (auto e = earray.begin(); e != earray.end(); e++)
        {
            // Create a record.
            Record record;
            Json::Value current = earray[e.index()];
            // Set the pid of the record.
            record.pid = current["pid"].asString();

            // Set the start time of the record.
            record.start = current["start"].asString();

            // Set the stop time of the record.
            record.stop = current["stop"].asString();

            // Add the record to the vector.
            records.push_back(record);
        }

        // Add the vector to the map.
        map[process] = records;
    }
    return;
}

inline bool is_digits(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit); // C++11
}

inline static bool isValidTimestamp(std::string timestamp) {
    // Define a regular expression pattern for the valid timestamp format.
    std::regex pattern("^(\\d{4}:\\d{2}:\\d{2}:\\d{2}:\\d{2}:\\d{2}:\\d{3,6})$");

    // Use std::regex_match to check if the timestamp matches the pattern.
    return std::regex_match(timestamp, pattern);
}

// Function to convert a time string to milliseconds
inline static long long stringToMilliseconds(const std::string &timeFormat)
{
    std::istringstream ss(timeFormat);
    std::tm tm = {};
    ss >> std::get_time(&tm, "%Y:%m:%d:%H:%M:%S:");

    if (ss.fail())
    {
        throw std::invalid_argument("Failed to parse the time format.");
    }

    // Extract milliseconds part from the string
    std::string millisecondsString;
    ss >> millisecondsString;

    if (ss.fail())
    {
        throw std::invalid_argument("Failed to parse milliseconds.");
    }

    // Convert the milliseconds part to an integer
    int milliseconds = std::stoi(millisecondsString);

    // Calculate the time in milliseconds
    auto timePoint = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    timePoint += std::chrono::milliseconds(milliseconds);

    auto millisecondsDuration = std::chrono::duration_cast<std::chrono::milliseconds>(timePoint.time_since_epoch());

    return millisecondsDuration.count();
}

// Function to calculate the time range in milliseconds between two time strings
inline static long long getRange(const std::string &timeFormat1, const std::string &timeFormat2)
{
    long long ms1 = stringToMilliseconds(timeFormat1);
    long long ms2 = stringToMilliseconds(timeFormat2);

    if (ms1 == -1 || ms2 == -1)
    {
        return -1; // An error occurred during conversion
    }

    // Calculate the time range in milliseconds
    long long rangeInMilliseconds = ms2 - ms1;

    return rangeInMilliseconds;
}

inline static std::string vectorToString(const std::vector<std::string> &vector)
{
    std::string res;
    for (const std::string &s : vector)
        res += ", " + s;
    return res;
}

#endif // COMMONS_H