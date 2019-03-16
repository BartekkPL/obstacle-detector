#include "data_presenter.hpp"

#include <opencv2/imgproc.hpp>

namespace sl {

cv::Mat DataPresenter::DrawMatches(const cv::Mat &img1,
    const std::vector<cv::KeyPoint> &keypoints1, const cv::Mat &img2,
    const std::vector<cv::KeyPoint> &keypoints2,
    const std::vector<cv::DMatch> &matches) {
  cv::Mat result;
  cv::drawMatches(img1, keypoints1, img2, keypoints2, matches,
                result, cv::Scalar::all(-1), cv::Scalar::all(-1),
                std::vector<char>(),
                cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
  return result;
}

cv::Mat DataPresenter::DrawMatchesTransformVector(const cv::Mat &img,
    const std::vector<cv::KeyPoint> &keypoints1,
    const std::vector<cv::KeyPoint> &keypoints2,
    const std::vector<cv::DMatch> &matches) {
  cv::Mat result = img.clone();
  for (auto &match : matches) {
    cv::line(result, keypoints1[match.queryIdx].pt,
        keypoints2[match.trainIdx].pt, cv::Scalar(255, 0, 0));
  }
  return result;
}

} // namespace sl
