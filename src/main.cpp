#include <iostream>

#include <opencv2/opencv.hpp>

#include "config.hpp"
#include "easylogging++.hpp"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char** argv) {
  // Load configuration from file
  el::Configurations conf(EASYLOGGING_CONFIG_FILE_PATH);
  // Reconfigure logger
  el::Loggers::reconfigureLogger("default", conf);
  el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);

  if (argc != 2) {
    std::cout << "Usage: display_image.img\n";
    return -1;
  }

  cv::Mat image = cv::imread(argv[1], 1);

  if (!image.data) {
    LOG(ERROR) << "No image data \n";
    return -1;
  }

  cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
  cv::imshow("Display Image", image);

  cv::waitKey(0);

  return 0;
}
