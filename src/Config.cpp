// Config.cpp
#include "Config.h"

// Constructor for the Config class; it receives a path to a configuration file as a parameter.
// During the construction, it opens the specified file, reads its contents into a JSON object,
// and then assigns specific values from the JSON object to the corresponding class variables.
Config::Config(const std::string &fpath)
{
  LOG(INFO) << "Creating Config object";

  // Define an input file stream and open the file specified by fpath
  std::ifstream f(fpath);
  if (!f.is_open()) // Checking if the file opened correctly
  {
    throw std::runtime_error("Error opening the file at path: " + fpath);
  }

  // Stream file contents into settings, which should be formatted as a JSON-style object
  if (!(f >> settings)) // Checking for errors while reading JSON from file
  {
    throw std::runtime_error("Error reading JSON from file at path: " + fpath);
  }

  if (settings.isMember("events_file_path") && settings.isMember("insights_file_path") && settings.isMember("sleep_interval") && settings.isMember("approximation") && settings.isMember("white_list")) // Checking for required keys in JSON file
  {
    // Get specific values from settings JSON object and store them into class variables
    events_file_path = get({"events_file_path"});
    insights_file_path = get({"insights_file_path"});
    sleep_interval = settings["sleep_interval"].asInt();
    approximation = settings["approximation"].asDouble();

    // Parse a list from the JSON object and store it into the class variable white_list
    to_list(settings["white_list"], white_list);
  }
  else
  {
    throw std::runtime_error("Missing required keys in JSON file");
  }

  // Close the file stream
  f.close();
  if (f.fail()) // Checking if closing the file caused an error
  {
    throw std::runtime_error("Error closing the file at path: " + fpath);
  }
}

Config::~Config()
{
  LOG(INFO) << "Destructing Config object";
}

std::string Config::get(const std::string &key)
{
  if (settings.isMember(key))
  {
    return settings[key].asString();
  }
  else
  {
    throw std::runtime_error("Missing key in JSON file: " + key);
  }
}

void Config::to_list(const Json::Value &json_array, std::list<std::string> &list)
{
  if (json_array.isArray())
  {
    for (const Json::Value &value : json_array)
    {
      list.push_back(value.asString());
    }
  }
  else
  {
    throw std::runtime_error("The supplied JSON value is not an array");
  }
}