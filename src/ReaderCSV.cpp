// ReaderCSV.cpp
#include "Reader.h"

Reader::Reader(const std::string& sfp) : rows()
{
    LOG(INFO) << "Creating Reader object";
    file.open(sfp, std::ios::in);
    if (!file.is_open()) LOG(WARNING) << "Could not open events file for read " << sfp;
}

Reader::~Reader()
{
    LOG(INFO) << "Destructing Reader object";
    if (file.is_open()) file.close();
}

bool Reader::isValidRow(const std::vector<std::string>& row)
{ 
    if (row.empty()) return false;
    return true;
}

// Read the Data from the file as string vector and add it to the Mapper
std::vector<std::vector<std::string>>& Reader::start()
{
    if (!file.is_open()) return;
    LOG(INFO) << "Start Reader";
    std::vector<std::string> row;
    std::string line, word;

    while (std::getline(file, line))
    {
        DLOG(INFO) << "READ_LINE: " << line;
        row.clear();

        std::stringstream s(line);
        // read every column data of a row and
        // store it in a string variable, 'word'
        // add it to the row vector.
        while (std::getline(s, word, ',')) row.push_back(word);
        if (isValidRow(row)) rows.push_back(row);
    }
    return rows;
}