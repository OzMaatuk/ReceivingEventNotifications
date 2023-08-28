#include <glog/logging.h>
#include <gtest/gtest.h>

int main(int argc, char **argv) {
    // Initialize Google’s logging flags.
    FLAGS_log_dir = "D:\\Workspace\\WindowsProcessMonitoring\\ReceivingEventNotifications\\logs";
    FLAGS_alsologtostderr = 1;
    // Initialize Google’s logging library.
    google::InitGoogleLogging("TEST");
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}