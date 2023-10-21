// Config.h
#ifndef CONFIG_H
#define CONFIG_H

#include <glog/logging.h>
#include <fstream>
#include <string>
#include <json/json.h>
#include <json/writer.h>

class Config
{
private:
    Json::Value settings;
    std::string stf;
    void to_vector(const Json::Value& json_array, std::vector<std::string>& vector);

public:
    std::string events_file_path;
    std::string insights_file_path;
    int sleep_interval;
    double approximation;
    std::vector<std::string> white_list;
    
    Config(const std::string& fpath);
    virtual ~Config();
    virtual std::string get(const std::string& key);
};

#endif // CONFIG_H