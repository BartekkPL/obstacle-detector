/**
 * Copyright 2019 Bartłomiej Kunikowski
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *s
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OBSTACLE_DETECTOR_DATA_PRESENTER_HPP_
#define OBSTACLE_DETECTOR_DATA_PRESENTER_HPP_

#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv4/opencv2/xfeatures2d.hpp>

#include "utils.hpp"

namespace od {

class DataPresenter {
 public:
  /**
   * @brief   Draws frame that is respected as danger area on image
   * @param [in] img    Image where danger frame will be drawn
   * @param [in] frame  Frame that will be drawn
   * @return  Image with danger frame
   */
  static cv::Mat DrawDangerFrame(const cv::Mat &img, const cv::Rect &frame);

  /**
   * @brief   Draws matches between two frames
   * @param [in] img            First image
   * @param [in] keypoints      Keypoints on first image
   * @param [in] img_next       Next image
   * @param [in] keypoint_next  Keypoints on second image
   * @param [in] matches        Matches between two images
   * @return  Image that is made with two frames and matches between them
   */
  static cv::Mat DrawMatches(const cv::Mat &img,
      const std::vector<cv::KeyPoint> &keypoints, const cv::Mat &img_next,
      const std::vector<cv::KeyPoint> &keypoints_next,
      const std::vector<cv::DMatch> &matches);

  /**
   * @brief   Draws translation between matched features as vectors on second
   *          image
   * @param [in] img      First image
   * @param [in] vectors  Vectors to be drawn
   * @return  Image with feature points translation vectors
   */
  static cv::Mat DrawTransformVectors(const cv::Mat &img,
      const std::vector<od::utils::Line> vectors);

  /**
   * @brief   Draws frame that is respected as warning area on image
   * @param [in] img  Image where warning frame will be drawn
   * @param [in] frame  Frame that will be drawn
   * @return  Image with warning frame
   */
  static cv::Mat DrawWarningFrame(const cv::Mat &img, const cv::Rect &frame);

};

} // namespace od

#endif // OBSTACLE_DETECTOR_DATA_PRESENTER_HPP_
