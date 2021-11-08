#include <cstdlib>

#include "frontends/file_frontend.h"
#include "backends/visual_backend.h"

int main(int argc, char* argv[]) {
  std::string image_directory = "./images";
  if (argc > 1) image_directory = argv[1];

  constexpr std::uint8_t display_height = 8, display_width = 12;
  auto frontend = file_frontend<display_width, display_height>{image_directory};
  auto backend = visual_backend<display_width, display_height>{};

  animator<decltype(frontend), decltype(backend)> anim{std::move(frontend), std::move(backend)};

  while (!anim.is_done()) {
    anim.generate_output();
  }

  return EXIT_SUCCESS;
}
