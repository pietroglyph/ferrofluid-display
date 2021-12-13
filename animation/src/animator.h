#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

template <std::size_t width, std::size_t height>
using frame = std::array<std::uint8_t, width * height>;

template <typename frontend, typename backend> class animator {
public:
  animator(frontend &&front, backend &&back)
      : front{std::move(front)}, back{std::move(back)} {}

  auto generate_output() {
    // Type of frame is typically frame<width, height>, but it's significantly
    // easier to use auto so we don't need template template parameters
    auto frame = front.get_frame();
    if (front.is_done())
      return;
    return back.generate_output(frame);
  }

  bool is_done() { return front.is_done(); }

private:
  frontend front;
  backend back;

  bool has_repeated_frame;
};
