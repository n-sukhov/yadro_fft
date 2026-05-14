#pragma once

#include <complex>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <cstddef>
#include <stdexcept>
#include <filesystem>

inline void ensure_data_dir(const std::string& data_dir) {
    // Проверка наличия папки для сохранения данных / её создание
    if (!std::filesystem::exists(data_dir)) {
        std::filesystem::create_directories(data_dir);
    }
}

inline void csv_write(
    const std::string& filename,
    const std::vector<std::complex<double>>& data
) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Can't open the file: " + filename);
    }

    file << std::setprecision(16);

    file << "index,real,imag\n";

    for (std::size_t i = 0; i < data.size(); ++i) {
        file << i << ","
             << data[i].real() << ","
             << data[i].imag() << "\n";
    }
}