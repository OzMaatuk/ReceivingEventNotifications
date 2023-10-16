// WriterCSV.cpp
#include "Writer.h"

Writer::Writer(std::string& ofp)
{
    LOG(INFO) << "Creating Writer object";
    file.open(ofp, std::ios::out | std::ios::app);
    if (!file.is_open()) LOG(WARNING) << "Could not open events file for writing " << ofp;
}

Writer::~Writer()
{
    LOG(INFO) << "Destructing Writer object";
    file.close();
}

void Writer::start(std::vector<std::vector<std::string>>& cache)
{
    if (!file.is_open()) return;
    LOG(INFO) << "Start Writer";
    // Export the events list to a CSV file.
    for (auto event : cache)
    {
        std::stringstream ss;
        for (auto e : event)
        {
            ss << e;
            ss << ",";
        }
        file << "\n" << ss.str();
        file.flush();
    }
}