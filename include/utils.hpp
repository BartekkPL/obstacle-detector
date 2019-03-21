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

#ifndef OBSTACLE_DETECTOR_UTILS_HPP_
#define OBSTACLE_DETECTOR_UTILS_HPP_

#include <opencv2/opencv.hpp>

namespace od {
namespace utils {

using Line = std::pair<cv::Point, cv::Point>;

/**
 * @brief   Gets frame that is recognized as danger area in the vision
 *          obstacle detection method
 * @param [in] img_size   Size of image
 * @return  Danger frame
 */
cv::Rect GetDangerFrame(const cv::Size &img_size);

/**
 * @brief   Gets frame that is recognized as warning area in the vision
 *          obstacle detection method
 * @param [in] img_size   Size of image
 * @return  Warning frame
 */
cv::Rect GetWarningFrame(const cv::Size &img_size);

/**
 * @brief   Gets offset for danger frame coordinates
 * @param [in] img_size   Size of image
 * @return  Danger frame offset
 */
cv::Point GetDangerOffset(const cv::Size &img_size);

/**
 * @brief   Gets offset for warning frame coordinates
 * @param [in] img_size   Size of image
 * @return  Warning frame offset
 */
cv::Point GetWarningOffset(const cv::Size &img_size);

} // namespace utils
} // namespace od

#endif  // OBSTACLE_DETECTOR_UTILS_HPP_
