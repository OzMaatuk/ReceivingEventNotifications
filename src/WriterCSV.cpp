// WriterCSV.cpp
#include "Writer.h"

Writer::Writer(const std::string& ofp)
{
    LOG(INFO) << "Creating Writer object";
    file.open(ofp, std::ios::out | std::ios::app);
    if (!file.is_open())
    {
        LOG(ERROR) << "Could not open events file for writing " << ofp;
        throw std::runtime_error("Could not open events file for writing: " + ofp);
    }
}

Writer::~Writer()
{
    LOG(INFO) << "Destructing Writer object";
    if (file.is_open()) file.close();
}

void Writer::start(const std::list<std::vector<std::string>>& cache)
{
    if (!file.is_open())
    {
        LOG(ERROR) << "Could not open CSV file.";
        throw std::runtime_error("Could not open CSV file.");
    }
    LOG(INFO) << "Start Writer";
    // Write the events list to a CSV file.
    // Think try/catch isn't neccesarry.
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

    if (file.fail())
    {
        LOG(ERROR) << "Error occurred while writing to the file.";
        throw MyException("Error occurred while writing to the file.");
    }
}