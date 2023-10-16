// Analyzer.h
#ifndef ANALYZER_H
#define ANALYZER_H

#include "Commons.h"

class Analyzer
{
private:
    double apx = 1.0;
    std::string* outputFilePath;
    std::map<std::string, std::string>* insights;
    std::vector<std::string>* wl;
    bool checkWhitelist(const std::string& process);
    std::tuple<bool, double> analyze(const std::vector<Record>& records);

public:
    Analyzer(const std::string& ofp);
    Analyzer(const Config& c);
    virtual ~Analyzer();

    void setConfig(const Config& c);
    void setApproximation(const double approximation);
    void setWhitelist(const std::vector<std::string>& white_list);

    virtual void load(const std::string& ofp);
    virtual void add(const std::string& process, const std::vector<Record>& records);
    virtual void start(const std::map<std::string, std::vector<Record>>& map);
    virtual void toFile();
};

#endif // ANALYZER_H