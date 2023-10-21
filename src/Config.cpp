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
  to_list(settings["white_list"], white_list);
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

void Config::to_list(const Json::Value &json_array, std::list<std::string> &list)
{
  for (const Json::Value &value : json_array)
  {
    list.push_back(value.asString());
  }
}