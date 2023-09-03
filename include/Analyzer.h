// Analyzer.h
#ifndef ANALYZER_H
#define ANALYZER_H

#define ADD_LABEL "ADD"
#define REJECT_LABEL "REJECT"

#include "Commons.h"

class Analyzer
{
private:
    double apx = 1.0;
    long DAYS_IN_MILLISECONDS = 86400000;
    long HOURS_IN_MILLISECONDS = 3600000;
    long MINUTES_IN_MILLISECONDS = 60000;
    long SECONDS_IN_MILLISECONDS = 1000;
    std::string ofp;
    std::map<std::string, std::vector<Record>> map;
    std::map<std::string, std::vector<std::string>> insights;
    void mapToInsights(std::map<std::string, std::vector<Record>>& smap);
    long getRange(std::string start, std::string stop);
    std::string MillisecondsToString(long milliseconds);
    bool filter(std::string process);
    bool ValidateTimestamp(std::string timestamp);
    std::tuple<std::string, long> analyze(std::vector<Record> records);

public:
    Analyzer(std::string sfpath, std::string ofpath);
    Analyzer(std::map<std::string, std::vector<Record>>& smap, std::string ofpath);
    ~Analyzer();
    void setApproximation(double approximation);
    void load();
    void add(std::string process, std::vector<Record> records);
    void toFile();
};

#endif // ANALYZER_H