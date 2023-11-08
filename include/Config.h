// Config.h
#ifndef CONFIG_H
#define CONFIG_H

#include <glog/logging.h>
#include <fstream>
#include <string>
#include <list>
#include <stdexcept>
#if defined(_WIN32) || defined(_WIN64)
#include "json/json.h"
#include <json/writer.h>
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__) || defined(__unix) || defined(__unix__)
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/writer.h>
#endif

/**
 * @class Config
 * @brief A class provides configuration object for the application
 *
 * This class is responsible for parsing, storing and suppling configuration parameters for the application.
 */
class Config
{
private:
    Json::Value settings; // Json variable to contain the configuration
    const std::string sfp; // configuration source file path
    void to_list(const Json::Value& json_array, std::list<std::string>& list); // helper function to convert Json array to std::list

public:
    std::string events_file_path; // path to the file storing event data
    std::string insights_file_path; // path to the file for storing insights data
    int sleep_interval; // the interval for the application to sleep (in seconds)
    double approximation; // approximation value for any calculations (given as a decimal fraction)
    std::list<std::string> white_list; // list to hold any strings for white listing
    
    Config(const std::string& fpath);
    virtual ~Config();
    virtual std::string get(const std::string& key); // method to get value of a particular setting by its key
};

#endif // CONFIG_H