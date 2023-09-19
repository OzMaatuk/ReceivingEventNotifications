// Config.h
#ifndef CONFIG_H
#define CONFIG_H

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
    std::string output_file_path;
    std::string insights_file_path;
    int sleep_interval;
    double approximation;
    std::vector<std::string> white_list;
    Config(std::string fpath);
    ~Config();
    std::string get(std::string key);
};

#endif // CONFIG_H