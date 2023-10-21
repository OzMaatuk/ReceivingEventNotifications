#include <glog/logging.h>
#include <gtest/gtest.h>

#define NDEBUG

int main(int argc, char **argv)
{
    // Initialize Google’s logging flags.
    FLAGS_log_dir = "D:\\Workspace\\WindowsProcessMonitoring\\ReceivingEventNotifications\\logs";
    FLAGS_alsologtostderr = 1;
    int res;
    // Initialize Google’s logging library.
    google::InitGoogleLogging("TEST");
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::GTEST_FLAG(filter) = "TestReaderCSV.*";
    res &= RUN_ALL_TESTS();
    ::testing::GTEST_FLAG(filter) = "TestWriterCSV.*";
    res &= RUN_ALL_TESTS();
    ::testing::GTEST_FLAG(filter) = "TestMapper.*";
    res &= RUN_ALL_TESTS();
    ::testing::GTEST_FLAG(filter) = "TestAnalyzer.*";
    res &= RUN_ALL_TESTS();
    ::testing::GTEST_FLAG(filter) = "TestIntegration.*";
    res &= RUN_ALL_TESTS();
    return res;
}