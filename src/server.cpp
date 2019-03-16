#include <chrono>
#include <iostream>
#include <thread>

#include <opencv2/opencv.hpp>

#include "config.hpp"
#include "easylogging++.hpp"
#include "server_tcp.hpp"

INITIALIZE_EASYLOGGINGPP

using namespace std::chrono_literals;

int main(int argc, char** argv) {
  // Load configuration from file
  el::Configurations conf(EASYLOGGING_CONFIG_FILE_PATH);
  // Reconfigure logger
  el::Loggers::reconfigureLogger("default", conf);
  el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);

  sl::connection::ServerTCP server_tcp(50000);

  if (!server_tcp.Start()) {
    return -1;
  }

  std::thread server_thread(&sl::connection::ServerTCP::Run, &server_tcp);

  cv::namedWindow("Display window", cv::WINDOW_NORMAL);
  cv::resizeWindow("Display Window", cv::Size(600, 600));

  while (true) {
    auto data = server_tcp.GetRawData();

    if (data.size() == 0) {
      // LOG(WARNING) << "Data size is 0";
      std::this_thread::sleep_for(10ms);
      continue;
    } else {
      LOG(DEBUG) << "Data size is " << data.size();
    }

    cv::Mat img = cv::imdecode(data, cv::IMREAD_ANYCOLOR);
    cv::imshow("Display window", img);

    int key = (cv::waitKey(20) & 0xFF);
    if (key == 'q') break;
  }

  server_tcp.Stop();

  server_thread.join();
}
