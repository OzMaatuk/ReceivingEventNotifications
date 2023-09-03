#ifndef TEST_MAPPER_C
#define TEST_MAPPER_C

#include <glog/logging.h>
#include <gtest/gtest.h>
#include "Mapper.h"

// Compaile with Mapper.cpp

class TestMapper : public ::testing::Test
{
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    TestMapper()
    {
        // You can do set-up work for each test here.
    }

    ~TestMapper() override
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

public:
    static void testJsonCpp()
    {
        Json::Value event;
        Json::Value vec(Json::arrayValue);
        vec.append(Json::Value(1));
        vec.append(Json::Value(2));
        vec.append(Json::Value(3));

        event["competitors"]["home"]["name"] = "Liverpool";
        event["competitors"]["away"]["code"] = 89223;
        event["competitors"]["away"]["name"] = "Aston Villa";
        event["competitors"]["away"]["code"] = vec;

        // std::cout << event << std::endl;
        LOG(INFO) << event;
    }
};

TEST(TestMapper, DISABLED_Simple_Test)
{
    LOG(INFO) << "TestMapper Simple_Test Started";
    Mapper map("..\\test_data\\test_map.json");
    LOG(INFO) << "Adding element 1";
    map.add({"23:35:23:95", "__InstanceCreationEvent", "backgroundTaskHost.exe", "24160"});
    LOG(INFO) << "Adding element 2";
    map.add({"23:35:53:95", "__InstanceDeletionEvent", "backgroundTaskHost.exe", "24160"});
    LOG(INFO) << "Adding element 3";
    map.add({"23:35:53:95", "__InstanceDeletionEvent", "backgroundTaskHost2.exe", "24190"});
    LOG(INFO) << "Adding element 4";
    map.add({"23:35:53:95", "__InstanceDeletionEvent", "backgroundTaskHost.exe", "24160"});
    LOG(INFO) << "Adding element 5";
    map.add({"23:35:53:95", "__InstanceCreationEvent", "backgroundTaskHost2.exe", "24190"});
    LOG(INFO) << "Adding element 6";
    map.add({"23:35:53:95", "__InstanceEvent", "backgroundTaskHost2.exe", "24190"});
    LOG(INFO) << "Adding element 7";
    map.add({"23:35:53:95", "__InstanceCreationEvent", "", "54190"});
    LOG(INFO) << "Adding element 8";
    map.add({"23:35:53:95", "__InstanceCreationEvent", "process1.exe", "24190"});
    LOG(INFO) << "executing toFile";
    map.toFile();
    EXPECT_NO_THROW();
}

#endif // TEST_MAPPER_C