#ifndef LOCALIZATOR_SELF_LOCALIZATOR_HPP_
#define LOCALIZATOR_SELF_LOCALIZATOR_HPP_

#include <vector>

#include <opencv2/opencv.hpp>

namespace sl {

class SelfLocalizator {
 public:
  void FeaturePointsDetect(const cv::Mat& img,
                           std::vector<cv::KeyPoint> &keypoints);

  void FeatureMatch(const cv::Mat &img1, const cv::Mat &img2,
                    std::vector<cv::KeyPoint> &keypoints1,
                    std::vector<cv::KeyPoint> &keypoints2,
                    std::vector<cv::DMatch> &good_matches);
 private:

};

} // namespace sl

#endif  // LOCALIZATOR_SELF_LOCALIZATOR_HPP_
