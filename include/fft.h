#pragma once

#include <cstddef>
#include <complex>
#include <vector>

class FFT {
private:
    static constexpr double PI = 3.14159265358979323846;

    static std::size_t choose_radix(std::size_t n);
    static void check_length(std::size_t n);
    static void transform(std::vector<std::complex<double>>& array, bool inverse);

public:
    FFT() {};
    std::vector<std::complex<double>> fft(const std::vector<std::complex<double>>& signal) const;
    std::vector<std::complex<double>> ifft(const std::vector<std::complex<double>>& spectrum) const;
};