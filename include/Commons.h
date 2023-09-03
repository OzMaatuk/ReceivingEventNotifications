// Commons.h
#ifndef COMMONS_H
#define COMMONS_H

#include <glog/logging.h>
#include <json/json.h>
#include <json/writer.h>
#include <fstream>
#include <vector>
#include <map>
#include "Record.h"
#include "MyException.h"

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

#endif // COMMONS_H