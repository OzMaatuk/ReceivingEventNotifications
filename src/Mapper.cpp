// Mapper.cpp
#include "Mapper.h"

Mapper::Mapper(): map()
{
    LOG(INFO) << "Creating Mapper object";
     #ifdef _WIN32
        startLabel = WIN_PROCESS_START;
        stopLabel = WIN_PROCESS_END;
    #elif _WIN64
        startLabel = WIN_PROCESS_START;
        stopLabel = WIN_PROCESS_END;
    #elif __APPLE__ || __MACH__
        startLabel = UNIX_PROCESS_START;
        stopLabel = UNIX_PROCESS_START;
    #elif __linux__
        startLabel = UNIX_PROCESS_START;
        stopLabel = UNIX_PROCESS_START;
    #elif __unix || __unix__
        startLabel = UNIX_PROCESS_START;
        stopLabel = UNIX_PROCESS_START;
    #else
        throw MyException("Cannot determine OS type.")
    #endif
}

Mapper::Mapper(const std::string& sfp) : Mapper()
{
    load(sfp);
}

Mapper::~Mapper()
{
    LOG(INFO) << "Desctucring Mapper object";
    // delete map;
}

void Mapper::addToKey(const std::string& key, const Record& r)
{
    VLOG(1) << "addToKey()";
    if (!map.contains(key))
        map.insert({std::string(key), {Record(r)}});
    else
        map.at(key).push_back(r);
}

void Mapper::setEndTime(const std::string& key, const std::string& pid, const std::string& ts)
{
    VLOG(1) << "setEndTime()";
    if (map.contains(key))
    {
        for (auto it = map.at(key).begin(); it != map.at(key).end(); ++it)
        {
            if ((it->pid.compare(pid) == 0) && (it->stop.compare("") == 0))
            {
                it->stop.assign(ts);
                return;
            }
        }
    }
    LOG(WARNING) << "No start time for proccess, pid: " << key << " " << pid;
}

void Mapper::load(const std::list<std::vector<std::string>>& rows)
{
    for (auto x : rows)
    {
        add(x);
    }
}

void Mapper::load(const std::string& sfp)
{
    loadMapFile(sfp, map);
}

void Mapper::add(const std::vector<std::string>& row)
{
    std::string pName = row.at(2);
    LOG(INFO) << "Adding event for process " << pName;
    std::string ts = row.at(0);
    std::string pid = row.at(3);
    std::string type = row.at(1);
    if (!type.empty())
    {
        if (type.compare(startLabel) == 0) // If it's a start event
        {
            addToKey(pName, {pid, ts, ""});
            return;
        }
        else if (type.compare(stopLabel) == 0) // If it's a stop event
        {
            setEndTime(pName, pid, ts);
            return;
        }
    }
    LOG(WARNING) << "Undefined event type";
    // throw MyException("Undefined event type");
}

void Mapper::start(const std::list<std::vector<std::string>>& cache)
{
    for (auto e : cache) add(e);
}

void Mapper::toFile(const std::string& ofp) const
{
    LOG(INFO) << "Creating process map file " << ofp;
    // Create a JSON object to store the map.
    Json::Value root = Json::objectValue;
    for (auto it = map.begin(); it != map.end(); ++it)
    {
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
    std::ofstream ofile(ofp);
    ofile << root.toStyledString();
    ofile.flush();
    ofile.close();
}

void Mapper::print() const
{
    printRecordsMap(map);
}


std::map<std::string, std::list<Record>>& Mapper::getMap()
{
    return map;
}