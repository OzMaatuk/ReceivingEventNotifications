#ifndef TEST_READERCSV_C
#define TEST_READERCSV_C

#include <glog/logging.h>
#include <gtest/gtest.h>
#include "Reader.h"

// Compaile with ReadCSV.cpp and Mapper.cpp

class TestReadCSV : public ::testing::Test
{
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    TestReadCSV()
    {
        // You can do set-up work for each test here.
    }

    ~TestReadCSV() override
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override
    {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    void TearDown() override
    {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
};

TEST(TestReadCSV, Simple_Test)
{
    LOG(INFO) << "TestReadCSV Simple_Test Started";
    Reader reader("..\\test_data\\test_events.csv", "..\\test_data\\test_map.json");
    LOG(INFO) << "reader.start()";
    reader.start();
    LOG(INFO) << "reader.getMap().toFile()";
    reader.getMap().toFile();
    EXPECT_NO_THROW();
    LOG(INFO) << "TestReadCSV Simple_Test Done";
}

#endif // TEST_READERCSV_C