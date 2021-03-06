#include <cstdlib>

#include <chrono>
#include <limits>

#include "backends/file_backend.h"
#include "backends/visual_backend.h"
#include "frontends/file_frontend.h"

int main(int argc, char *argv[]) {
  std::string image_directory = "./images";
  std::string output_file = "./out.anim";
  if (argc == 2)
    image_directory = argv[1];
  else if (argc > 2) {
    image_directory = argv[1];
    output_file = argv[2];
  }

  using namespace std::chrono_literals;
  constexpr std::uint8_t display_height = 4, display_width = 4;
  auto frontend = file_frontend<display_width, display_height>{image_directory};
  auto backend = file_backend<display_width, display_height, std::uint16_t>{
      output_file, 3.5s, 4095};

  animator<decltype(frontend), decltype(backend)> anim{std::move(frontend),
                                                       std::move(backend)};

  while (!anim.is_done()) {
    anim.generate_output();
  }

  return EXIT_SUCCESS;
}
