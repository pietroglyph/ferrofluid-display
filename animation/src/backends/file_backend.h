#pragma once

#include <chrono>
#include <cstdint>
#include <filesystem>
#include <fmt/format.h>
#include <fstream>
#include <limits>
#include <thread>

#include "../animator.h"

template <std::size_t width, std::size_t height, typename duty_cycle_t>
class file_backend {
public:
  file_backend(
      std::filesystem::path file_path,
      std::chrono::duration<double, std::milli> frame_time,
      duty_cycle_t max_duty_cycle = std::numeric_limits<duty_cycle_t>::max())
      : frame_time{frame_time}, max_duty_cycle{max_duty_cycle} {
    serial_mode = std::filesystem::is_character_file(file_path);
    if (std::filesystem::exists(file_path) && !serial_mode)
      throw std::runtime_error{"Output file already exists"};
    else if (serial_mode)
      fmt::print("Output file is a character device so we will switch to "
                 "serial mode\n");

    file_stream = std::ofstream{std::filesystem::absolute(file_path).string()};
    if (!file_stream.is_open()) {
      throw std::runtime_error{
          "Couldn't open output file for reading and writing"};
    }

    if (serial_mode) {
      // Make sure everything is off and then put us into serial mode
      file_stream << "OFF:"
                  << "\n"
                  << "SER:" << std::endl;
    }
    file_stream << width << "," << height << std::endl;
  }

  void generate_output(frame<width, height> fr) {
    for (std::size_t i = 0; i < fr.size(); i++) {
      if (i != 0)
        file_stream << ',';
      file_stream << static_cast<duty_cycle_t>(
          static_cast<double>(fr[i]) /
          std::numeric_limits<std::uint8_t>::max() * max_duty_cycle);
    }
    file_stream << std::endl; // We want to flush the stream when writing to
                              // serial, which is why we use std::endl here

    if (serial_mode) {
      // Avoid filling up the buffer by sending right before the frame is done
      // and the MCU wants a new frame
      std::this_thread::sleep_for(frame_time / 0.95);
    }
  }

private:
  std::ofstream file_stream;
  std::chrono::duration<double, std::milli> frame_time;
  std::uint16_t max_duty_cycle;
  bool serial_mode;
};
