#include "gtest/gtest.h"

#include "config.hpp"
#include "easylogging++.hpp"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char** argv) {
  // Load configuration from file
  el::Configurations conf(EASYLOGGING_CONFIG_FILE_PATH);
  // Reconfigure logger
  el::Loggers::reconfigureLogger("default", conf);
  el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
