#ifndef TEST_ANALYZER_C
#define TEST_ANALYZER_C

#include <glog/logging.h>
#include <gtest/gtest.h>
#include "Analyzer.h"

class TestAnalyzer : public ::testing::Test
{
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    TestAnalyzer()
    {
        // You can do set-up work for each test here.
    }

    ~TestAnalyzer() override
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

TEST(TestAnalyzer, Simple_Test)
{
    LOG(INFO) << "TestAnalyzer Simple_Test Started";
    Analyzer a("..\\test_data\\test_map.json", "..\\test_data\\test_insights.json");

    LOG(INFO) << "a.toFile()";
    a.toFile();

    EXPECT_NO_THROW();
    LOG(INFO) << "TestAnalyzer Simple_Test Done";
}

#endif // TEST_ANALYZER_C