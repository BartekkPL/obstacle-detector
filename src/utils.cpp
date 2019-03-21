#include "utils.hpp"

namespace sl {
namespace utils {

cv::Rect GetDangerFrame(const cv::Size &img_size) {
  int x = img_size.width / 6;
  int y = img_size.height / 6;
  return {x, y, img_size.width - 2 * x, img_size.height - 2 * y};
}

cv::Point GetDangerOffset(const cv::Size &img_size) {
  cv::Rect rect = GetDangerFrame(img_size);
  return {rect.x, rect.y};
}

cv::Rect GetWarningFrame(const cv::Size &img_size) {
  int x = img_size.width / 9;
  int y = img_size.height / 9;
  return {x, y, img_size.width - 2 * x, img_size.height - 2 * y};
}

cv::Point GetWarningOffset(const cv::Size &img_size) {
  cv::Rect rect = GetWarningFrame(img_size);
  return {rect.x, rect.y};
}

} // namespace utils
} // namespace sl
