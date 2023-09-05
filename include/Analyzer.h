// Analyzer.h
#ifndef ANALYZER_H
#define ANALYZER_H

#include "Commons.h"

class Analyzer
{
private:
    double apx = 1.0;
    std::string ofp;
    std::map<std::string, std::vector<Record>> map;
    std::map<std::string, std::vector<std::string>> insights;
    std::vector<std::string> wl;
    bool checkWhitelist(std::string process);
    std::tuple<bool, double> analyze(std::vector<Record> records);
    void setConfig(Config c);

public:
    Analyzer(std::string sfpath, std::string ofpath);
    Analyzer(std::map<std::string, std::vector<Record>>& smap, std::string ofpath);
    Analyzer(std::string sfpath, std::string ofpath, Config c);
    Analyzer(std::map<std::string, std::vector<Record>>& smap, std::string ofpath, Config c);
    ~Analyzer();
    void setApproximation(double approximation);
    void setWhitelist(std::vector<std::string> white_list);
    void load();
    void add(std::string process, std::vector<Record> records);
    void start();
    void toFile();
};

#endif // ANALYZER_H