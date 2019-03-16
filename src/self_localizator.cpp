#include "self_localizator.hpp"

#ifndef HAVE_OPENCV_XFEATURES2D
#error "This code needs the xfeatures2d contrib module to be run."
#endif

#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv4/opencv2/xfeatures2d.hpp>

namespace {
// Configuration

const int MIN_HESSIAN = 400;
const float TRESH_RATIO = 0.6f;

} // namespace

namespace sl {

void SelfLocalizator::FeaturePointsDetect(const cv::Mat& img,
    std::vector<cv::KeyPoint> &keypoints) {
  cv::Ptr<cv::xfeatures2d::SURF> detector =
      cv::xfeatures2d::SURF::create(MIN_HESSIAN);
  detector->detect(img, keypoints);
}

void SelfLocalizator::FeatureMatch(const cv::Mat &img1, const cv::Mat &img2,
                  std::vector<cv::KeyPoint> &keypoints1,
                  std::vector<cv::KeyPoint> &keypoints2,
                  std::vector<cv::DMatch> &good_matches) {
  cv::Ptr<cv::xfeatures2d::SURF> detector =
      cv::xfeatures2d::SURF::create(MIN_HESSIAN);
  cv::Mat descriptors1, descriptors2;

  detector->detectAndCompute(img1, cv::noArray(), keypoints1, descriptors1);
  detector->detectAndCompute(img2, cv::noArray(), keypoints2, descriptors2);

  cv::Ptr<cv::DescriptorMatcher> matcher =
      cv::DescriptorMatcher::create(cv::DescriptorMatcher::FLANNBASED);

  std::vector<std::vector<cv::DMatch>> knn_matches;
  matcher->knnMatch(descriptors1, descriptors2, knn_matches, 2);

  for (size_t i = 0; i < knn_matches.size(); ++i) {
    if (knn_matches[i][0].distance < TRESH_RATIO * knn_matches[i][1].distance) {
      good_matches.push_back(knn_matches[i][0]);
    }
  }
}

} // namespace sl
