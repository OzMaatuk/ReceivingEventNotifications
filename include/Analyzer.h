// Analyzer.h
#ifndef ANALYZER_H
#define ANALYZER_H

#include "Commons.h"

class Analyzer
{
private:
    double apx = 1.0;
    std::string outputFilePath;
    std::map<std::string, std::vector<std::string>> insights;
    std::vector<std::string> wl;
    bool checkWhitelist(std::string process);
    std::tuple<bool, double> analyze(std::vector<Record> records);

public:
    Analyzer(std::string ofp);
    Analyzer(std::string ofp, Config c);
    ~Analyzer();

    void setConfig(Config c);
    void setApproximation(double approximation);
    void setWhitelist(std::vector<std::string> white_list);

    void load(std::string ofp);
    void add(std::string process, std::vector<Record> records);
    void start(std::map<std::string, std::vector<Record>>& map);
    void toFile();
};

#endif // ANALYZER_H