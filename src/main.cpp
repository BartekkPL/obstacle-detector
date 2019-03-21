#include <chrono>
#include <iostream>
#include <thread>

#include <opencv2/opencv.hpp>

#include "config.hpp"
#include "easylogging++.hpp"

#include "data_presenter.hpp"
#include "self_localizator.hpp"
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
  img1 = img.clone();

  while(cam.isOpened()) {
    cam >> img2;

    std::vector<cv::KeyPoint> keypoints1, keypoints2;
    std::vector<cv::DMatch> good_matches;
    sl::SelfLocalizator::FeatureMatch(
        /**cv::Mat(img1, sl::utils::GetWarningFrame(img1.size())),
        cv::Mat(img2, sl::utils::GetWarningFrame(img2.size())),*/
        img1, img2, keypoints1, keypoints2, good_matches);
    cv::Mat img_matches;

    std::vector<sl::utils::Line> lines =
        sl::SelfLocalizator::FilterTransformVectors(
        sl::SelfLocalizator::GetTransformVectors(keypoints1, keypoints2,
        good_matches, /*sl::utils::GetWarningOffset(img2.size())*/{0, 0}));

    img = sl::DataPresenter::DrawTransformVectors(img2, lines);

    img = sl::DataPresenter::DrawWarningFrame(img,
        sl::utils::GetWarningFrame(img.size()));

    img = sl::DataPresenter::DrawDangerFrame(img,
        sl::utils::GetDangerFrame(img.size()));

    std::vector<cv::Rect> partitions =
        sl::SelfLocalizator::FindPotentialObstaclePartitions(lines);

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
