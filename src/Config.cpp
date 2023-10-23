// Config.cpp
#include "Config.h"

// Constructor for the Config class; it receives a path to a configuration file as a parameter.
// During the construction, it opens the specified file, reads its contents into a JSON object,
// and then assigns specific values from the JSON object to the corresponding class variables.
Config::Config(const std::string& fpath)
{
  LOG(INFO) << "Creating Config object";
  
  //Define an input file stream and open the file specified by fpath
  std::ifstream f(fpath);
  
  //Stream file contents into settings, which should be formatted as a JSON-style object
  f >> settings;

  //Get specific values from settings JSON object and store them into class variables
  events_file_path = get({"events_file_path"});
  insights_file_path = get({"insights_file_path"});
  sleep_interval = settings["sleep_interval"].asInt();
  approximation = settings["approximation"].asDouble();
  
  //Parse a list from the JSON object and store it into the class variable white_list
  to_list(settings["white_list"], white_list);
  
  //Close the file stream
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