#ifndef TEST_INTEGRATION_C
#define TEST_INTEGRATION_C

#include <glog/logging.h>
#include <gtest/gtest.h>
#include "Analyzer.h"
#include "Reader.h"

class TestIntergration : public ::testing::Test
{
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    TestIntergration()
    {
        // You can do set-up work for each test here.
    }

    ~TestIntergration() override
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

TEST(TestIntergration, Simple_Test)
{
    LOG(INFO) << "TestIntergration Simple_Test Started";

    LOG(INFO) << "Settingup Reader";
    Reader reader("..\\data\\M_events.csv", "..\\data\\M_test.json");
    LOG(INFO) << "reader.start()";
    reader.start();

    LOG(INFO) << "Settingup Analyzer";
    Analyzer analyzer(reader.getMap().getMap(), "..\\data\\M_insights.json");
    LOG(INFO) << "analyzer.toFile();";
    analyzer.toFile();

    EXPECT_NO_THROW();
    LOG(INFO) << "TestIntergration Simple_Test Done";
}

#endif // TEST_INTEGRATION_C