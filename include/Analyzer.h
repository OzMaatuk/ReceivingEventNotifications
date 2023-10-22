// Analyzer.h
#ifndef ANALYZER_H
#define ANALYZER_H

#include "Commons.h"

class Analyzer
{
private:
    double timingApx = 1.0;
    const std::string outputFilePath;
    std::list<std::string> wl;
    std::map<std::string, std::map<std::string, std::string>> insights;
    bool checkWhitelist(const std::string& process) const;
    const std::string isMaliciousTiming(const std::list<Record>& records) const;
    std::map<std::string, std::string> analyze(const std::list<Record>& records);

public:
    Analyzer(const std::string& ofp);
    Analyzer(const Config& c);
    virtual ~Analyzer();

    virtual void setConfig(const Config& c);
    virtual void setTimingApproximation(const double approximation);
    virtual void setWhitelist(const std::list<std::string>& white_list);

    virtual void load(const std::string& ofp);
    virtual void add(const std::string& process, const std::list<Record>& records);
    virtual void start(const std::map<std::string, std::list<Record>>& map);
    virtual void toFile() const;
    virtual std::map<std::string, std::map<std::string, std::string>>& getInsights();
};

#endif // ANALYZER_H