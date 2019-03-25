#include <chrono>
#include <iostream>
#include <thread>

#include <opencv2/opencv.hpp>

#include "config.hpp"
#include "easylogging++.hpp"

#include "data_presenter.hpp"
#include "obstacle_detector.hpp"
#include "utils.hpp"

INITIALIZE_EASYLOGGINGPP

using namespace std::chrono_literals;

int main(int argc, char** argv) {
  // Load configuration from file
  el::Configurations conf(EASYLOGGING_CONFIG_FILE_PATH);
  // Reconfigure logger
  el::Loggers::reconfigureLogger("default", conf);
  el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);

  cv::Mat img1, img2;
  cv::VideoCapture cam;
  cam.open(0);

  cv::Mat img;
  cam >> img;

  cv::resize(img, img, cv::Size(), 0.5, 0.5);
  cv::flip(img, img, -1);
  img1 = img.clone();

  while(cam.isOpened()) {
    cam >> img2;
    cv::resize(img2, img2, cv::Size(), 0.5, 0.5);
    cv::flip(img2, img2, -1);
    
    std::vector<cv::KeyPoint> keypoints1, keypoints2;
    std::vector<cv::DMatch> good_matches;
    od::ObstacleDetector::FeatureMatch(
        cv::Mat(img1, od::utils::GetWarningFrame(img1.size())),
        cv::Mat(img2, od::utils::GetWarningFrame(img2.size())),
        /*img1, img2,*/ keypoints1, keypoints2, good_matches);
    cv::Mat img_matches;

    std::vector<od::utils::Line> lines =
        od::ObstacleDetector::FilterTransformVectors(
        od::ObstacleDetector::GetTransformVectors(keypoints1, keypoints2,
        good_matches, od::utils::GetWarningOffset(img2.size())/*{0, 0}*/));

    img = od::DataPresenter::DrawTransformVectors(img2, lines);

    img = od::DataPresenter::DrawWarningFrame(img,
        od::utils::GetWarningFrame(img.size()));

    img = od::DataPresenter::DrawDangerFrame(img,
        od::utils::GetDangerFrame(img.size()));

    std::vector<cv::Rect> partitions =
        od::ObstacleDetector::FindPotentialObstaclePartitions(lines);

    for (auto &partition : partitions) {
      cv::rectangle(img, partition, {0, 255, 0});
    }

    cv::imshow("Display Image", img);
    char ch = cv::waitKey(10);
    if (ch == 27) {
      std::cout << "\rESC Key pressed, Exiting." << std::endl;
      break;
    }
    img1 = img2.clone();
  }

  return 0;
}
