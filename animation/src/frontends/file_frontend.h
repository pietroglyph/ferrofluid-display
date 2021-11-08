#pragma once

#include <cstdint>
#include <filesystem>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include <fmt/format.h>

#include "../animator.h"

template <std::uint8_t width, std::uint8_t height>
class file_frontend {
public:
  file_frontend(std::filesystem::path images_directory) : images_directory{images_directory} {
    if (!std::filesystem::exists(images_directory)) throw std::runtime_error{fmt::format("{} doesn't exist", images_directory.string())};
    if (!std::filesystem::is_directory(images_directory)) throw std::runtime_error{fmt::format("{} is not a directory", images_directory.string())};
  }

  frame<width, height> get_frame() {
    frame<width, height> fr;

    auto file = images_directory.append(fmt::format("./{}.png", current_image_idx++));
    if (!std::filesystem::exists(file)) {
      done = true;
      return fr;
    }

    // Unfortunately there's no way to pass a premade cv::Mat into cv::imread
    auto fr_mat = cv::imread(file.string());
    if (fr_mat.rows != width || fr_mat.cols != height) throw std::runtime_error{fmt::format("{} has the wrong size", file.string())};

    std::copy(fr_mat.begin<std::uint8_t>(), fr_mat.end<std::uint8_t>(), std::begin(fr));
    fr_mat.addref();

    return fr;
  }

  bool is_done() {
    return done;
  }

private:
  unsigned int current_image_idx = 0;
  std::filesystem::path images_directory;

  bool done = false;
};
