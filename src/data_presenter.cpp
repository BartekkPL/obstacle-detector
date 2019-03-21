#include "data_presenter.hpp"

#include <opencv2/imgproc.hpp>

#include "self_localizator.hpp"

namespace sl {

cv::Mat DataPresenter::DrawDangerFrame(const cv::Mat &img,
                                       const cv::Rect &frame) {
  cv::Mat result = img.clone();
  cv::Scalar danger_color(0, 0, 255);
  cv::rectangle(result, frame, danger_color);
  return result;
}

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

cv::Mat DataPresenter::DrawTransformVectors(const cv::Mat &img,
    const std::vector<sl::utils::Line> vectors) {
  cv::Mat result = img.clone();
  for (auto &line : vectors) {
    cv::line(result, line.first, line.second, cv::Scalar(255, 0, 0));
  }
  return result;
}

cv::Mat DataPresenter::DrawWarningFrame(const cv::Mat &img,
                                        const cv::Rect &frame) {
  cv::Mat result = img.clone();
  cv::Scalar warning_color(0, 255, 255);
  cv::rectangle(result, frame, warning_color);
  return result;
}

} // namespace sl
