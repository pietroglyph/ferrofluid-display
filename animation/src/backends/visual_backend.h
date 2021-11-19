#pragma once

#include <cstddef>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "../animator.h"

template <std::size_t width, std::size_t height>
class visual_backend {
public:
  void generate_output(frame<width, height> fr) {
    cv::Mat fr_mat{height, width, CV_8UC1, fr.data()};
    cv::imshow("Display Preview", fr_mat);    
    cv::waitKey();
  }
};
