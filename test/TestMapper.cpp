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

TEST(TestMapper, Simple_Test)
{
    LOG(INFO) << "TestMapper Simple_Test Started";
    Mapper map("..\\test_data\\simple_test_map.json");

    // Should get approximation > 0.3
    map.add({"23:35:23:95", "__InstanceCreationEvent", "backgroundTaskHost.exe", "24160"});
    map.add({"23:35:53:95", "__InstanceDeletionEvent", "backgroundTaskHost.exe", "24160"});

    map.add({"23:35:33:95", "__InstanceCreationEvent", "backgroundTaskHost.exe", "24160"});
    map.add({"23:35:53:95", "__InstanceDeletionEvent", "backgroundTaskHost.exe", "24160"});

    map.add({"23:35:53:95", "__InstanceCreationEvent", "backgroundTaskHost.exe", "24160"});
    map.add({"23:36:03:95", "__InstanceDeletionEvent", "backgroundTaskHost.exe", "24160"});

    map.add({"23:36:23:95", "__InstanceCreationEvent", "backgroundTaskHost.exe", "24160"});
    map.add({"23:36:53:95", "__InstanceDeletionEvent", "backgroundTaskHost.exe", "24160"});

    map.add({"23:37:23:95", "__InstanceCreationEvent", "backgroundTaskHost.exe", "24160"});
    map.add({"23:37:53:95", "__InstanceDeletionEvent", "backgroundTaskHost.exe", "24160"});

    map.add({"23:38:23:95", "__InstanceCreationEvent", "backgroundTaskHost.exe", "24160"});
    map.add({"23:38:53:95", "__InstanceDeletionEvent", "backgroundTaskHost.exe", "24160"});

    map.add({"23:39:23:95", "__InstanceCreationEvent", "backgroundTaskHost.exe", "24160"});
    map.add({"23:39:53:95", "__InstanceDeletionEvent", "backgroundTaskHost.exe", "24160"});

    map.add({"24:44:23:95", "__InstanceCreationEvent", "backgroundTaskHost.exe", "24160"});
    map.add({"24:45:53:95", "__InstanceDeletionEvent", "backgroundTaskHost.exe", "24160"});

    // Should get approximation 0.0
    map.add({"23:35:23:95", "__InstanceCreationEvent", "backgroundTaskHost2.exe", "24160"});
    map.add({"23:35:53:95", "__InstanceDeletionEvent", "backgroundTaskHost2.exe", "24160"});

    map.add({"23:35:23:95", "__InstanceCreationEvent", "backgroundTaskHost2.exe", "24160"});
    map.add({"23:35:53:95", "__InstanceDeletionEvent", "backgroundTaskHost2.exe", "24160"});

    map.add({"23:35:23:95", "__InstanceCreationEvent", "backgroundTaskHost2.exe", "24160"});
    map.add({"23:35:53:95", "__InstanceDeletionEvent", "backgroundTaskHost2.exe", "24160"});

    map.add({"23:35:23:95", "__InstanceCreationEvent", "backgroundTaskHost2.exe", "24160"});
    map.add({"23:35:53:95", "__InstanceDeletionEvent", "backgroundTaskHost2.exe", "24160"});

    map.add({"23:35:23:95", "__InstanceCreationEvent", "backgroundTaskHost2.exe", "24160"});
    map.add({"23:35:53:95", "__InstanceDeletionEvent", "backgroundTaskHost2.exe", "24160"});

    map.add({"24:35:23:95", "__InstanceCreationEvent", "backgroundTaskHost2.exe", "24160"});
    map.add({"24:35:53:95", "__InstanceDeletionEvent", "backgroundTaskHost2.exe", "24160"});

    map.add({"24:35:23:95", "__InstanceCreationEvent", "backgroundTaskHost2.exe", "24160"});
    map.add({"24:35:53:95", "__InstanceDeletionEvent", "backgroundTaskHost2.exe", "24160"});

    map.add({"24:35:23:95", "__InstanceCreationEvent", "backgroundTaskHost2.exe", "24160"});
    map.add({"24:35:53:95", "__InstanceDeletionEvent", "backgroundTaskHost2.exe", "24160"});

    LOG(INFO) << "executing toFile";
    map.toFile();
    EXPECT_NO_THROW();
    LOG(INFO) << "TestMapper Simple_Test Done";
}

TEST(TestMapper, DISABLED_Unkown_Element_Type_Exception) // throw exception was removed.
{
    LOG(INFO) << "TestMapper Unkown_Element_Type_Exception Started";
    Mapper map("..\\test_data\\undefined_test_map.json");
    LOG(INFO) << "Adding undefined type element";
    EXPECT_THROW({
        map.add({"23:35:53:95", "__InstanceEvent", "backgroundTaskHost2.exe", "24190"});
    }, MyException);
    LOG(INFO) << "TestMapper Unkown_Element_Type_Exception Done";
}

TEST(TestMapper, Edge_Cases_Test)
{
    LOG(INFO) << "TestMapper Edge_Cases_Test Started";
    Mapper map("..\\test_data\\edgecases_test_map.json");

    // Assuming timestamps are valid and increasing.

    LOG(INFO) << "Adding element 1";
    map.add({"23:35:23:95", "__InstanceCreationEvent", "backgroundTaskHost.exe", "24160"});
    LOG(INFO) << "Adding element 2";
    map.add({"23:35:53:95", "__InstanceDeletionEvent", "backgroundTaskHost.exe", "24160"});
    LOG(INFO) << "Adding element 3";
    map.add({"23:35:53:95", "__InstanceDeletionEvent", "backgroundTaskHost2.exe", "24190"});
    LOG(INFO) << "Adding element 4";
    map.add({"23:45:53:95", "__InstanceDeletionEvent", "backgroundTaskHost.exe", "24160"});
    LOG(INFO) << "Adding element 5";
    map.add({"23:55:53:95", "__InstanceCreationEvent", "backgroundTaskHost2.exe", "24190"});
    LOG(INFO) << "Adding element 7";
    map.add({"23:65:53:95", "__InstanceCreationEvent", "", "54190"});
    LOG(INFO) << "Adding element 8";
    map.add({"24:05:53:95", "__InstanceCreationEvent", "process1.exe", "24190"});
    LOG(INFO) << "Adding element 9";
    map.add({"24:05:53:95", "__InstanceCreationEvent", "backgroundTaskHost2.exe", "24190"});
    LOG(INFO) << "Adding element 10";
    map.add({"24:15:53:95", "__InstanceDeletionEvent", "backgroundTaskHost2.exe", "24190"});
    LOG(INFO) << "Adding element 11";
    map.add({"24:25:53:95", "__InstanceDeletionEvent", "process1.exe", "24199"});
    LOG(INFO) << "Adding element 12";
    map.add({"24:35:53:95", "__InstanceDeletionEvent", "backgroundTaskHost.exe", "24160"});
    LOG(INFO) << "Adding element 13";
    map.add({"24:35:53:95", "__InstanceDeletionEvent", "backgroundTaskHost2.exe", "24190"});
    LOG(INFO) << "Adding element 14";
    map.add({"24:45:53:95", "__InstanceCreationEvent", "process1.exe", "24190"});

    LOG(INFO) << "executing toFile";
    map.toFile();
    EXPECT_NO_THROW();
    LOG(INFO) << "TestMapper Edge_Cases_Test Done";
}

#endif // TEST_MAPPER_C