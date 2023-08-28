// Config.cpp
#include "Config.h"

Config::Config(std::string fpath) {
    std::ifstream f(fpath);
    f >> settings;
    os = get( { "os" } );
    events_file_path = get( { "events_file_path" } );
    output_file_path = get( { "output_file_path" } );
    insights_file_path = get( { "insights_file_path" } );
    f.close();
}

Config::~Config() {
    
}

std::string Config::get(std::string key) {
    return settings[key].asString();
}