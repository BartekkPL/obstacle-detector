#include <chrono>
#include <iostream>
#include <thread>

#include <opencv2/opencv.hpp>

#include "config.hpp"
#include "easylogging++.hpp"

#include "client_tcp.hpp"
#include "data_presenter.hpp"
#include "self_localizator.hpp"
#include "server_tcp.hpp"

INITIALIZE_EASYLOGGINGPP

using namespace std::chrono_literals;

int main(int argc, char** argv) {
  // Load configuration from file
  el::Configurations conf(EASYLOGGING_CONFIG_FILE_PATH);
  // Reconfigure logger
  el::Loggers::reconfigureLogger("default", conf);
  el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);

  sl::connection::ClientTCP client_tcp("127.0.0.1", 50000);
  sl::connection::ServerTCP server_tcp(50000);

  if (!server_tcp.Start()) {
    return -1;
  }

  std::thread t_server(&sl::connection::ServerTCP::Run, &server_tcp);

  if (!client_tcp.Connect()) {
    return -1;
  }

  std::this_thread::sleep_for(10s);
  server_tcp.Stop();

  // //-- Draw keypoints
  // sl::SelfLocalizator localizator;

  // cv::Mat img1, img2;
  // cv::VideoCapture cam;
  // cam.open(0);

  // while(cam.isOpened()) {
  //   cam >> img1;
  //   cam >> img2;

  //   std::vector<cv::KeyPoint> keypoints1, keypoints2;
  //   std::vector<cv::DMatch> good_matches;
  //   localizator.FeatureMatch(img1, img2, keypoints1, keypoints2, good_matches);
  //   cv::Mat img_matches;

  //   cv::imshow("Display Image", sl::DataPresenter::DrawMatchesTransformVector(
  //       img2, keypoints1, keypoints2, good_matches));
  //   char ch = cv::waitKey(10);
  //   // ESC Check
  //   if (ch == 27) {
  //     std::cout << "\rESC Key pressed, Exiting." << std::endl;
  //     break;
  //   }
  // }

  return 0;
}
