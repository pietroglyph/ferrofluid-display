#pragma once

#include <cstdint>
#include <filesystem>
#include <fstream>

#include "../animator.h"

template<std::size_t width, std::size_t height>
class file_backend {
public:
	file_backend(std::filesystem::path file_path) {
		if (std::filesystem::exists(file_path)) throw std::runtime_error{"File already exists"};

		file_stream = std::ofstream{std::filesystem::absolute(file_path).string()};
		file_stream << width << "," << height << "\n";
	}

	void generate_output(frame<width, height> fr) {
		for (std::size_t i = 0; i < fr.size(); i++) {
			if (i != 0) file_stream << ',';
			file_stream << fr[i];
		}
		file_stream << "\n";
	}
private:
	std::ofstream file_stream;
};
