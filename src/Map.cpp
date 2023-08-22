// Map.cpp
#include "Map.h"

Map::Map() {}

Map::~Map() {}

void Map::printvec(std::vector<std::string> vec) {
    for(size_t i=0; i<vec.size(); i++) {
            printf("%s", vec[i].c_str());
        }
}

void Map::printMap() {
    for (auto it = map.begin(); it != map.end(); ++it) {
        printf("ProcessName: %s\n", it->first.c_str());
        for (auto obj = it->second.begin(); obj != it->second.end(); ++obj) {
        printf("  PID: %s\n", obj->pid.c_str());
        printf("  Start: %s\n", obj->start.c_str());
        printf("  Stop: %s\n", obj->stop.c_str());
        }
    }
}

void Map::add(std::vector<std::string> row) {
    std::string pName = row.at(2);
    std::string ts = row.at(0);
    std::string pid = row.at(3);
    std::string type = row.at(1);
    if (type.compare(START)) 
    {
        map[pName].push_back(Record{ pid, ts, NULL });
    } else if (type.compare(END)) {
        std::vector<Record>::iterator it = map[pName].begin();
        while ( !(it->pid.compare(pid)) && (it->stop.c_str()) ) {
            it++;
        }
        if (it != map[pName].end()) {
            it->stop = ts;
        } else {
            // TODO: throw Exception
            printf("This event does not have starting point");
            printvec(row);
        }
    } else {
        // TODO: throw Exception
        printf("Undefined event type");
        printvec(row);
    }
}

void Map::toFile(std::string fpath) {
    // Create a JSON object to store the map.
    Json::Value root = Json::objectValue;
    for (auto it = map.begin(); it != map.end(); ++it) {
        Json::Value process = Json::arrayValue;
        for (auto obj = it->second.begin(); obj != it->second.end(); ++obj)
        {
            // Json::Value *Record;
            // ((*Record)["pid"]) = Json::Value(obj->pid);
            Json::Value Record = Json::objectValue;
            Record["pid"] = Json::Value(obj->pid);
            Record["start"] = Json::Value(obj->start);
            Record["stop"] = Json::Value(obj->stop);
            process.append(Record);
        }
        root[it->first] = process;
    }

    // Write the JSON object to a file.
    std::ofstream ofile(fpath);
    ofile << root.toStyledString();
    ofile.close();
}

void Map::testJsonCpp() {
    Json::Value event;   
    Json::Value vec(Json::arrayValue);
    vec.append(Json::Value(1));
    vec.append(Json::Value(2));
    vec.append(Json::Value(3));

    event["competitors"]["home"]["name"] = "Liverpool";
    event["competitors"]["away"]["code"] = 89223;
    event["competitors"]["away"]["name"] = "Aston Villa";
    event["competitors"]["away"]["code"]=vec;

    std::cout << event << std::endl;
    getchar();
}

// int main() {
//     Map map;
//     map.testJsonCpp();
//     return 1;
// }