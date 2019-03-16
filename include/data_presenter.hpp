#ifndef LOCALIZATOR_DATA_PRESENTER_HPP_
#define LOCALIZATOR_DATA_PRESENTER_HPP_

#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv4/opencv2/xfeatures2d.hpp>
#include <vector>

namespace sl {

class DataPresenter {
 public:
  static cv::Mat DrawMatches(const cv::Mat &img1,
      const std::vector<cv::KeyPoint> &keypoints1, const cv::Mat &img2,
      const std::vector<cv::KeyPoint> &keypoints2,
      const std::vector<cv::DMatch> &matches);

  static cv::Mat DrawMatchesTransformVector(const cv::Mat &img,
      const std::vector<cv::KeyPoint> &keypoints1,
      const std::vector<cv::KeyPoint> &keypoints2,
      const std::vector<cv::DMatch> &matches);
};

} // namespace sl

#endif // LOCALIZATOR_DATA_PRESENTER_HPP_
