// Config.cpp
#include "Config.h"

Config::Config(const std::string& fpath)
{
  LOG(INFO) << "Creating Config object";
  std::ifstream f(fpath);
  f >> settings;
  events_file_path = get({"events_file_path"});
  insights_file_path = get({"insights_file_path"});
  sleep_interval = settings["sleep_interval"].asInt();
  approximation = settings["approximation"].asDouble();
  to_vector(settings["white_list"], white_list);
  f.close();
}

Config::~Config()
{
  LOG(INFO) << "Destructing Config object";
}

std::string Config::get(const std::string& key)
{
  return settings[key].asString();
}

void Config::to_vector(const Json::Value &json_array, std::vector<std::string> &vector)
{
  for (const Json::Value &value : json_array)
  {
    vector.push_back(value.asString());
  }
}