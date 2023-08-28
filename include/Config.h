// Config.h
#ifndef CONFIG_H
#define CONFIG_H

#include <fstream>
#include <string>
#include <json/json.h>
#include <json/writer.h>

class Config {
    private:
        Json::Value settings;
        std::string stf;
    public:
        std::string os;
        std::string event_start_label;
        std::string event_end_label;
        std::string events_file_path;
        std::string output_file_path;
        std::string insights_file_path;
        Config(std::string fpath);
        ~Config();
        std::string get(std::string key);
};

#endif // CONFIG_H