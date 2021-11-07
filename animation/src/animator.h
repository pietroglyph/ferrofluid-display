#pragma once

#include <cstddef>
#include <cstdint>
#include <array>

template <std::size_t width, std::size_t height>
using frame = std::array<std::uint8_t, width * height>;

template <typename frontend, typename backend>
class animator {
public:
  animator(frontend&& front, backend&& back) : front{front}, back{back} {}

  auto generate_output() {
    // Type of frame is typically frame<width, height>, but it's significantly easier to use auto so we don't need template template parameters
    auto frame = front.get_frame();
    return back.generate_output(frame);
  } 

  bool is_done() {
    return front.is_done();
  }

private:
  frontend front;
  backend back;
};
