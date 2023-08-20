#include "json/json.h"
#include<json/writer.h>
#include "MapObj.h"
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

class Map {
    private: std::map<std::string, std::vector<MapObj>> map;

    public: Map() {
        
    }

    public: ~Map() {

    }

    private: void printvec(std::vector<std::string> vec) {
        for(int i=0; i<vec.size(); i++) {
                printf("%s", vec[i]);
            }
    }

    void printMap() {
        for (auto it = map.begin(); it != map.end(); ++it) {
            printf("ProcessName: %s\n", it->first.c_str());
            for (auto obj = it->second.begin(); obj != it->second.end(); ++obj) {
            printf("  PID: %s\n", obj->pid.c_str());
            printf("  Start: %s\n", obj->start.c_str());
            printf("  Stop: %s\n", obj->stop.c_str());
            }
        }
    }

    public: void add(std::vector<std::string> row) {
        std::string pName = row.at(2);
        std::string ts = row.at(0);
        std::string pid = row.at(3);
        std::string type = row.at(1);
        if (type.compare(START)) 
        {
            map[pName].push_back(MapObj{ pid, ts, NULL });
        } else if (type.compare(END)) {
            std::vector<MapObj>::iterator it = map[pName].begin();
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

    void toFile(std::string fpath) {
        // Create a JSON object to store the map.
        Json::Value root = Json::objectValue;
        for (auto it = map.begin(); it != map.end(); ++it) {
            Json::Value process = Json::arrayValue;
            for (auto obj = it->second.begin(); obj != it->second.end(); ++obj)
            {
                // Json::Value *mapObj;
                // ((*mapObj)["pid"]) = Json::Value(obj->pid);
                Json::Value mapObj = Json::objectValue;
                mapObj["pid"] = Json::Value(obj->pid);
                mapObj["start"] = Json::Value(obj->start);
                mapObj["stop"] = Json::Value(obj->stop);
                process.append(mapObj);
            }
            root[it->first] = process;
        }

        // Write the JSON object to a file.
        std::ofstream ofile(fpath);
        ofile << root.toStyledString();
        ofile.close();
    }

        void testJsonCpp() {
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
};

// int main() {
//     Map map;
//     map.testJsonCpp();
//     return 1;
// }