// Analyzer.h
#ifndef ANALYZER_H
#define ANALYZER_H

#include "Commons.h"

class Analyzer
{
private:
    double timingApx = 1.0;
    std::string outputFilePath;
    std::vector<std::string> wl;
    std::map<std::string, std::map<std::string, std::string>> insights;
    bool checkWhitelist(const std::string& process);
    std::string isMaliciousTiming(const std::vector<Record>& records);
    std::map<std::string, std::string> analyze(const std::vector<Record>& records);

public:
    Analyzer(const std::string& ofp);
    Analyzer(const Config& c);
    virtual ~Analyzer();

    void setConfig(const Config& c);
    void setTimingApproximation(const double approximation);
    void setWhitelist(const std::vector<std::string>& white_list);

    virtual void load(const std::string& ofp);
    virtual void add(const std::string& process, const std::vector<Record>& records);
    virtual void start(const std::map<std::string, std::vector<Record>>& map) = 0;
    virtual void toFile() = 0;
    std::map<std::string, std::map<std::string, std::string>>& getInsights();
};

#endif // ANALYZER_H