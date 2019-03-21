#ifndef LOCALIZATOR_SELF_UTILS_HPP_
#define LOCALIZATOR_SELF_UTILS_HPP_

#include <opencv2/opencv.hpp>

namespace sl {
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
} // namespace sl

#endif  // LOCALIZATOR_SELF_UTILS_HPP_
