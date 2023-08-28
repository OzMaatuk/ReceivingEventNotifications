// Mapper.cpp
#include "Mapper.h"

Mapper::Mapper(std::string fpath) {
    ofp = fpath;
    // std::ofstream ofile(ofp);
}

Mapper::~Mapper() {}

std::string Mapper::vectorToString(const std::vector<std::string>& vector) {
  std::string res;
  for (const std::string& s : vector) res += ", " + s;
  return res;
}

std::string Mapper::getStartLabel() { return "__InstanceCreationEvent"; }
std::string Mapper::getStopLabel() { return "__InstanceDeletionEvent"; }

void Mapper::print() {
    for (auto it = map.begin(); it != map.end(); ++it) {
        printf("ProcessName: %s\n", it->first.c_str());
        for (auto obj = it->second.begin(); obj != it->second.end(); ++obj) {
        printf("  PID: %s\n", obj->pid.c_str());
        printf("  Start: %s\n", obj->start.c_str());
        printf("  Stop: %s\n", obj->stop.c_str());
        }
    }
}

void Mapper::addToKey(std::string key, Record r) {
    if (!map.contains(key)) map.insert({ key, { r } });
    else map[key].push_back( r );
}

void Mapper::setEndTime(std::string key, std::string pid, std::string ts) {
    if (map.contains(key)) {
        std::vector<Record>::iterator it = map[key].begin();
        while ( !(it->pid.compare(pid) == 0) && (it->stop.empty()) ) { it++; }
        if (it != map[key].end()) {
            it->stop = ts;
            return;
        }
    }
    LOG(WARNING) << "No start time for proccess, pid: " << key << pid;
}

void Mapper::add(std::vector<std::string> row) {
    std::string pName = row.at(2);
    std::string ts = row.at(0);
    std::string pid = row.at(3);
    std::string type = row.at(1);
    if (!type.empty()) {
        if (type.compare(getStartLabel()) == 0) {
            addToKey(pName, { pid, ts, "" } );
            return;
        } else if (type.compare(getStopLabel()) == 0) {
            setEndTime(pName, pid, ts);
            return;
        }
    }
    DLOG(INFO) << vectorToString(row);
    throw Exception("Undefined event type");
}

void Mapper::toFile() {
    // Create a JSON object to store the map.
    Json::Value root = Json::objectValue;
    for (auto it = map.begin(); it != map.end(); ++it) {
        Json::Value process = Json::arrayValue;
        for (auto obj = it->second.begin(); obj != it->second.end(); ++obj)
        {
            Json::Value Record = Json::objectValue;
            Record["pid"] = Json::Value(obj->pid);
            Record["start"] = Json::Value(obj->start);
            Record["stop"] = Json::Value(obj->stop);
            process.append(Record);
        }
        root[it->first] = process;
    }
    // Write the JSON object to a file.
    DLOG(INFO) << root.toStyledString();
    std::ofstream ofile(ofp);
    ofile << root.toStyledString();
    ofile.flush();
    ofile.close();  
}