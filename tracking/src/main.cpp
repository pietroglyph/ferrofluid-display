#include <chrono>
#include <cstdlib>

#include <fmt/format.h>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

cv::Mat
process_hsv(cv::InputOutputArray frame,
            std::tuple<std::array<int, 3>, std::array<int, 3>> min_max_value) {
  static cv::Mat hsv_frame{frame.size(), CV_8UC3};
  cv::cvtColor(frame, hsv_frame, cv::COLOR_BGR2HSV);
  cv::GaussianBlur(
      hsv_frame, hsv_frame, {5, 5},
      0); // sigma_x = 0 implies that we get std devs from kernel size

  cv::Mat threshold_frame =
      hsv_frame; // Points to the same memory; we're just renaming here
  auto min = std::get<0>(min_max_value), max = std::get<1>(min_max_value);
  cv::inRange(hsv_frame, cv::Scalar(min[0], min[1], min[2]),
              cv::Scalar(max[0], max[1], max[2]), threshold_frame);

  std::vector<cv::Mat> contours;
  cv::findContours(threshold_frame, contours, cv::RETR_EXTERNAL,
                   cv::CHAIN_APPROX_SIMPLE);

  for (auto &&contour : contours) {
    double perimeter = cv::arcLength(contour, true);
    cv::approxPolyDP(contour, contour, 0.04 * perimeter, true);

    if (contour.size[0] != 4)
      continue;

    auto rect = cv::boundingRect(contour);
    fmt::print("Got rectangle of area {}\n", rect.area());
  }

  cv::drawContours(frame, contours, -1, {0, 0, 255});

  return threshold_frame;
}

cv::Mat process_hough(cv::Mat frame, int thresh_one, int thresh_two) {
  static cv::Mat gray_frame{frame.size(), CV_8UC1};
  cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY);

  cv::GaussianBlur(gray_frame, gray_frame, {3, 3},
                   0); // sigma_x = 0 implies std. dev comes from kernel size

  static cv::Mat edges{frame.size(), CV_8UC1};
  cv::Canny(gray_frame, edges, thresh_one, thresh_two);

  std::vector<cv::Mat> contours;
  cv::findContours(edges, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

  for (auto &&contour : contours) {
    double perimeter = cv::arcLength(contour, true);
    cv::approxPolyDP(contour, contour, 0.04 * perimeter, true);

    if (contour.size[0] != 4)
      continue;
    auto rect = cv::boundingRect(contour);
    if (std::abs(static_cast<double>(rect.height) / rect.width - 8.5 / 11) >
        0.08)
      continue;
    // if (rect.area() < 150'000 || rect.area() > 250'000) continue;

    cv::rectangle(frame, rect, {255, 0, 0});
    cv::putText(frame, fmt::format("area: {}", rect.area()),
                {rect.x + rect.width / 2, rect.y + rect.height / 2},
                cv::FONT_HERSHEY_SIMPLEX, 1, {255, 0, 0});

    fmt::print("Area: {}\tAspect ratio: {}\n", rect.area(),
               static_cast<double>(rect.height) / rect.width);
  }

  cv::drawContours(frame, contours, -1, {0, 0, 255});

  return edges;
}

int main(int argc, char *argv[]) {
  std::string vid_file_name = "/dev/video0";
  if (argc > 1)
    vid_file_name = argv[1];

  cv::VideoCapture vid_cap{vid_file_name};
  if (!vid_cap.isOpened())
    throw std::runtime_error{fmt::format("Couldn't open '{}'", vid_file_name)};

  constexpr auto window_name = "Video Input";
  cv::namedWindow(window_name, cv::WINDOW_GUI_NORMAL);

  constexpr auto threshold_window_name = "Thresholded Video";
  cv::namedWindow(threshold_window_name, cv::WINDOW_GUI_NORMAL);

  /*std::tuple<std::array<int, 3>, std::array<int, 3>> min_max_value;
  cv::createTrackbar("Min Hue", window_name, &std::get<0>(min_max_value)[0],
  255); cv::createTrackbar("Max Hue", window_name,
  &std::get<1>(min_max_value)[0], 255); cv::createTrackbar("Min Sat",
  window_name, &std::get<0>(min_max_value)[1], 255); cv::createTrackbar("Max
  Sat", window_name, &std::get<1>(min_max_value)[1], 255);
  cv::createTrackbar("Min Val", window_name, &std::get<0>(min_max_value)[2],
  255); cv::createTrackbar("Max Val", window_name,
  &std::get<1>(min_max_value)[2], 255);*/
  int thresh_one = 100, thresh_two = 200;
  cv::createTrackbar("Threshold One", window_name, &thresh_one, 255);
  cv::createTrackbar("Threshold Two", window_name, &thresh_two, 255);

  cv::Mat frame;
  auto last_frame_time = std::chrono::steady_clock::now();
  while (true) {
    auto fps = fmt::format(
        "{} us", std::chrono::duration_cast<std::chrono::microseconds>(
                     std::chrono::steady_clock::now() - last_frame_time)
                     .count());

    vid_cap.read(frame);

    auto thresholded_frame = process_hough(frame, thresh_one, thresh_two);

    cv::putText(frame, fps, {20, 30}, cv::FONT_HERSHEY_SIMPLEX, 1, {0, 255, 0});
    cv::imshow(window_name, frame);

    cv::imshow(threshold_window_name, thresholded_frame);

    cv::waitKey(1);
    last_frame_time = std::chrono::steady_clock::now();
  }

  return EXIT_SUCCESS;
}
