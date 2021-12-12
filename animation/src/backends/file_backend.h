#pragma once

#include <cstdint>
#include <filesystem>
#include <fmt/format.h>
#include <fstream>
#include <limits>

#include "../animator.h"

template <std::size_t width, std::size_t height, typename duty_cycle_t>
class file_backend {
public:
  file_backend(
      std::filesystem::path file_path,
      duty_cycle_t max_duty_cycle = std::numeric_limits<duty_cycle_t>::max())
      : max_duty_cycle{max_duty_cycle} {
    if (std::filesystem::exists(file_path))
      fmt::print("File already exists; we will append\n");

    file_stream = std::ofstream{std::filesystem::absolute(file_path).string()};
    file_stream << width << "," << height << "\n";
  }

  void generate_output(frame<width, height> fr) {
    for (std::size_t i = 0; i < fr.size(); i++) {
      if (i != 0)
        file_stream << ',';
      file_stream << static_cast<duty_cycle_t>(
          static_cast<double>(fr[i]) /
          std::numeric_limits<std::uint8_t>::max() * max_duty_cycle);
    }
    file_stream << "\n";
  }

private:
  std::ofstream file_stream;
  std::uint16_t max_duty_cycle;
};
