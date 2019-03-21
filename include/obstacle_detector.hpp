#ifndef OBSTACLE_DETECTOR_OBSTACLE_DETECTOR_HPP_
#define OBSTACLE_DETECTOR_OBSTACLE_DETECTOR_HPP_

#include <vector>

#include <opencv2/opencv.hpp>

#include "utils.hpp"

namespace od {

class ObstacleDetector {
 public:
  /**
   * @brief   Detects feature points on image
   * @param [in] img          Image where we looking for feature points
   * @param [out] keypoints   Found feature points
   */
  static void FeaturePointsDetect(const cv::Mat& img,
                                  std::vector<cv::KeyPoint> &keypoints);

  /**
   * @brief   Detects and matches features between two images
   * @param [in] img              First image
   * @param [in] img_next         Next image
   * @param [out] keypoints       Feature points on first image
   * @param [out] keypoints_next  Feature points on second image
   * @param [out] good_matches    Matches between feature points in both images
   */
  static void FeatureMatch(const cv::Mat &img, const cv::Mat &img_next,
                            std::vector<cv::KeyPoint> &keypoints,
                            std::vector<cv::KeyPoint> &keypoints_next,
                            std::vector<cv::DMatch> &good_matches);

  /**
   * @brief   Gets transform vectors of feature points between two frames
   * @param [in] keypoints        Feature points on first image
   * @param [in] keypoints_next   Feature points on second image
   * @param [in] matches          Matches between feature points in both images
   * @param [in] offset           Offset of keypoints
   * @return  Vector of transform vectors
   */
  static std::vector<utils::Line> GetTransformVectors(
      const std::vector<cv::KeyPoint> &keypoints,
      const std::vector<cv::KeyPoint> &keypoints_next,
      const std::vector<cv::DMatch> &matches,
      const cv::Point &offset);

  /**
   * @brief   Filters vectors that comes from camera noise
   * @param [in] vectors  Transform vectors to be filtered
   * @return  Filtered vector of vectors
   */
  static std::vector<utils::Line> FilterTransformVectors(
      const std::vector<utils::Line> &vectors);

  /**
   * @brief   Finds potential obstacles on image
   * @param [in] lines  Tranform vectors
   * @return  Frames around potential obstacles in scene
   */
  static std::vector<cv::Rect> FindPotentialObstaclePartitions(
      const std::vector<utils::Line> lines);
};

} // namespace od

#endif  // OBSTACLE_DETECTOR_OBSTACLE_DETECTOR_HPP_
