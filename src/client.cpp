#include <chrono>
#include <iostream>
#include <thread>

#include "client_tcp.hpp"
#include "config.hpp"
#include "easylogging++.hpp"

INITIALIZE_EASYLOGGINGPP

using namespace std::chrono_literals;

int main() {
// Load configuration from file
  el::Configurations conf(EASYLOGGING_CONFIG_FILE_PATH);
  // Reconfigure logger
  el::Loggers::reconfigureLogger("client", conf);
  el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);

  sl::connection::ClientTCP client_tcp("127.0.0.1", 50000);

  if (!client_tcp.Connect()) {
    return -1;
  }

  std::string data = "Some message";

  client_tcp.Send(data);

  std::this_thread::sleep_for(10s);

  return 0;
}
