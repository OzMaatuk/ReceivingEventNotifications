#ifndef TEST_WRITERCSV_C
#define TEST_WRITERCSV_C

#include <glog/logging.h>
#include <gtest/gtest.h>
#include "Writer.h"

class TestWriterCSV : public ::testing::Test
{
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    TestWriterCSV()
    {
        // You can do set-up work for each test here.
    }

    ~TestWriterCSV() override
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

TEST(TestWriterCSV, Simple_Test)
{
    LOG(INFO) << "TestWriterCSV Simple_Test Started";
    Writer writer = Writer("..\\test_data\\TestWriterCSV_events.csv");
    std::deque<std::vector<std::string>> tmp;

    // Should get approximation > 0.3
    tmp.push_back({"23:35:23:95", "__InstanceCreationEvent", "backgroundTaskHost.exe", "24160"});
    tmp.push_back({"23:35:53:95", "__InstanceDeletionEvent", "backgroundTaskHost.exe", "24160"});

    tmp.push_back({"23:35:33:95", "__InstanceCreationEvent", "backgroundTaskHost.exe", "24160"});
    tmp.push_back({"23:35:53:95", "__InstanceDeletionEvent", "backgroundTaskHost.exe", "24160"});

    tmp.push_back({"23:35:53:95", "__InstanceCreationEvent", "backgroundTaskHost.exe", "24160"});
    tmp.push_back({"23:36:03:95", "__InstanceDeletionEvent", "backgroundTaskHost.exe", "24160"});

    tmp.push_back({"23:36:23:95", "__InstanceCreationEvent", "backgroundTaskHost.exe", "24160"});
    tmp.push_back({"23:36:53:95", "__InstanceDeletionEvent", "backgroundTaskHost.exe", "24160"});

    tmp.push_back({"23:37:23:95", "__InstanceCreationEvent", "backgroundTaskHost.exe", "24160"});
    tmp.push_back({"23:37:53:95", "__InstanceDeletionEvent", "backgroundTaskHost.exe", "24160"});

    tmp.push_back({"23:38:23:95", "__InstanceCreationEvent", "backgroundTaskHost.exe", "24160"});
    tmp.push_back({"23:38:53:95", "__InstanceDeletionEvent", "backgroundTaskHost.exe", "24160"});

    tmp.push_back({"23:39:23:95", "__InstanceCreationEvent", "backgroundTaskHost.exe", "24160"});
    tmp.push_back({"23:39:53:95", "__InstanceDeletionEvent", "backgroundTaskHost.exe", "24160"});

    tmp.push_back({"24:44:23:95", "__InstanceCreationEvent", "backgroundTaskHost.exe", "24160"});
    tmp.push_back({"24:45:53:95", "__InstanceDeletionEvent", "backgroundTaskHost.exe", "24160"});

    // Should get approximation 0.0
    tmp.push_back({"23:35:23:95", "__InstanceCreationEvent", "backgroundTaskHost2.exe", "24160"});
    tmp.push_back({"23:35:53:95", "__InstanceDeletionEvent", "backgroundTaskHost2.exe", "24160"});

    tmp.push_back({"23:35:23:95", "__InstanceCreationEvent", "backgroundTaskHost2.exe", "24160"});
    tmp.push_back({"23:35:53:95", "__InstanceDeletionEvent", "backgroundTaskHost2.exe", "24160"});

    tmp.push_back({"23:35:23:95", "__InstanceCreationEvent", "backgroundTaskHost2.exe", "24160"});
    tmp.push_back({"23:35:53:95", "__InstanceDeletionEvent", "backgroundTaskHost2.exe", "24160"});

    tmp.push_back({"23:35:23:95", "__InstanceCreationEvent", "backgroundTaskHost2.exe", "24160"});
    tmp.push_back({"23:35:53:95", "__InstanceDeletionEvent", "backgroundTaskHost2.exe", "24160"});

    tmp.push_back({"23:35:23:95", "__InstanceCreationEvent", "backgroundTaskHost2.exe", "24160"});
    tmp.push_back({"23:35:53:95", "__InstanceDeletionEvent", "backgroundTaskHost2.exe", "24160"});

    tmp.push_back({"24:35:23:95", "__InstanceCreationEvent", "backgroundTaskHost2.exe", "24160"});
    tmp.push_back({"24:35:53:95", "__InstanceDeletionEvent", "backgroundTaskHost2.exe", "24160"});

    tmp.push_back({"24:35:23:95", "__InstanceCreationEvent", "backgroundTaskHost2.exe", "24160"});
    tmp.push_back({"24:35:53:95", "__InstanceDeletionEvent", "backgroundTaskHost2.exe", "24160"});

    tmp.push_back({"24:35:23:95", "__InstanceCreationEvent", "backgroundTaskHost2.exe", "24160"});
    tmp.push_back({"24:35:53:95", "__InstanceDeletionEvent", "backgroundTaskHost2.exe", "24160"});

    LOG(INFO) << "writer.start()";
    writer.start(tmp);
    EXPECT_NO_THROW();
    LOG(INFO) << "TestWriterCSV Simple_Test Done";
}

#endif // TEST_WRITERCSV_C