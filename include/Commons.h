// Commons.h
#ifndef COMMONS_H
#define COMMONS_H

#include <glog/logging.h>
#include <json/json.h>
#include <json/writer.h>
#include <fstream>
#include <vector>
#include <map>
#include "Config.h"
#include "Record.h"
#include "MyException.h"

inline static long HOURS_IN_MILLISECONDS = 3600000;
inline static long MINUTES_IN_MILLISECONDS = 60000;
inline static long SECONDS_IN_MILLISECONDS = 1000;

inline static void printRecordsMap(std::map<std::string, std::vector<Record>>& map)
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

inline static void loadMapFile(std::string sfp, std::map<std::string, std::vector<Record>>& map)
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

inline static bool isValidTimestamp(std::string timestamp)
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
        if ((timestamp[i] < '0' || timestamp[i] > '9') && timestamp[i] != ':')
        {
            return false;
        }
    }

    // The string is valid.
    return true;
}

inline static long stringToMilliseconds(std::string s)
{
    // Split the timestamps into their components.
    std::string digits;
    std::vector<long> components;
    std::stringstream ss(s);
    while (std::getline(ss, digits, ':'))
    {
        components.push_back(std::stoi(digits));
    }

    // Calculate the difference between the timestamps.
    long hours = components[0];
    long minutes = components[1];
    long seconds = components[2];
    long milliseconds = components[3];
    return HOURS_IN_MILLISECONDS * hours + MINUTES_IN_MILLISECONDS * minutes + SECONDS_IN_MILLISECONDS * seconds + milliseconds;
}

inline static long getRange(std::string start, std::string stop)
{
    long startMil = stringToMilliseconds(start);
    long stopMil = stringToMilliseconds(stop);
    return stopMil - startMil;
}

inline static std::string vectorToString(const std::vector<std::string> &vector)
{
    std::string res;
    for (const std::string &s : vector)
        res += ", " + s;
    return res;
}

#endif // COMMONS_H