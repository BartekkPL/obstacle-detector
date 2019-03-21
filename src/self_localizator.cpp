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
const float MIN_TRANSFORM = 5.0f;
const float MAX_TRANSFORM = 30.0f;
const float TRESH_RATIO = 0.6f;
const int THRESHOLD_RADIUS = 50;

} // namespace

namespace sl {

void SelfLocalizator::FeaturePointsDetect(const cv::Mat& img,
    std::vector<cv::KeyPoint> &keypoints) {
  cv::Ptr<cv::xfeatures2d::SURF> detector =
      cv::xfeatures2d::SURF::create(MIN_HESSIAN);
  detector->detect(img, keypoints);
}

void SelfLocalizator::FeatureMatch(const cv::Mat &img, const cv::Mat &img_next,
                  std::vector<cv::KeyPoint> &keypoints,
                  std::vector<cv::KeyPoint> &keypoints_next,
                  std::vector<cv::DMatch> &good_matches) {
  cv::Ptr<cv::xfeatures2d::SURF> detector =
      cv::xfeatures2d::SURF::create(MIN_HESSIAN);
  cv::Mat descriptors1, descriptors2;

  detector->detectAndCompute(img, cv::noArray(), keypoints, descriptors1);
  detector->detectAndCompute(img_next, cv::noArray(), keypoints_next,
      descriptors2);

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

std::vector<utils::Line> SelfLocalizator::GetTransformVectors(
    const std::vector<cv::KeyPoint> &keypoints1,
    const std::vector<cv::KeyPoint> &keypoints2,
    const std::vector<cv::DMatch> &matches,
    const cv::Point &offset) {
  std::vector<utils::Line> result;
  cv::Point2f offset_f = offset;
  for (auto &match : matches) {
    result.push_back(std::make_pair(keypoints1[match.queryIdx].pt + offset_f,
        keypoints2[match.trainIdx].pt + offset_f));
  }
  return result;
}

std::vector<utils::Line> SelfLocalizator::FilterTransformVectors(
    const std::vector<utils::Line> &vectors) {
  float distance_sum = 0.0;
  std::vector<utils::Line> result;
  std::vector<float> distances;
  int num = 0;

  for (auto &line : vectors) {
    distances.push_back(cv::norm(line.second - line.first));
    if (distances.back() > MAX_TRANSFORM || distances.back() < MIN_TRANSFORM)
      continue;
    distance_sum += distances.back();
    ++num;
  }

  float average_distance = distance_sum / (float)num;

  for (size_t i = 0; i < vectors.size(); ++i) {
    if (distances[i] < MAX_TRANSFORM && distances.back() < MIN_TRANSFORM
        && distances[i] >= average_distance)
      result.push_back(vectors[i]);
  }

  return result;
}

std::vector<cv::Rect> SelfLocalizator::FindPotentialObstaclePartitions(
    const std::vector<utils::Line> lines) {
  std::vector<int> labels;
  int threshold_power = THRESHOLD_RADIUS * THRESHOLD_RADIUS;
  std::vector<cv::Point> points;
  for (auto &line : lines) {
    points.push_back(line.second);
  }
  int num_labels = cv::partition(points, labels,
      [threshold_power](const cv::Point &lhs, const cv::Point &rhs) {
        return ((lhs.x - rhs.x) * (lhs.x - rhs.x) +
                (lhs.y - rhs.y) * (lhs.y - rhs.y)) < threshold_power;
      });

  std::vector<std::vector<cv::Point>> contours(num_labels);
  for (size_t i = 0; i < points.size(); ++i) {
    contours[labels[i]].push_back(points[i]);
  }

  std::vector<cv::Rect> boxes;
  for (size_t i = 0; i < contours.size(); ++i) {
    if (contours[i].size() < 10)
      continue;
    cv::Rect box = boundingRect(contours[i]);
    boxes.push_back(box);
  }

  return boxes;
}

} // namespace sl
