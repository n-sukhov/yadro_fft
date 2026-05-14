#include "fft.h"
#include <cmath>
#include <stdexcept>

std::size_t FFT::choose_radix(std::size_t n) {
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;
    if (n % 5 == 0) return 5;
    return 0;
}

void FFT::check_length(std::size_t n) {
    if (n == 0) {
        throw std::invalid_argument("Array length must be positive");
    }
    while (n % 2 == 0) n /= 2;
    while (n % 3 == 0) n /= 3;
    while (n % 5 == 0) n /= 5;

    if (n != 1) {
        throw std::invalid_argument("Array length must have only divisors 2, 3, 5");
    }
}

void FFT::transform(std::vector<std::complex<double>>& array, bool inverse) {
    const size_t N = array.size();
    if (N == 1) return;

    const size_t radix = choose_radix(N);
    if (radix == 0) {
        throw std::invalid_argument("Array length must have only divisors 2, 3, 5");
    }
    const size_t M = N / radix;

    std::vector<std::vector<std::complex<double>>> array_parts (
        radix, std::vector<std::complex<double>> (M)
    );

    for (size_t i = 0; i < radix; ++i) {
        for (size_t j = 0; j < M; ++j) {
            array_parts[i][j] = array[i + j * radix];
        }
        transform(array_parts[i], inverse);
    }

    const double sign = inverse ? 1.0 : -1.0;

    for (std::size_t i = 0; i < M; ++i) {
        for (std::size_t j = 0; j < radix; ++j) {
            const std::size_t k = i + M * j;

            std::complex<double> sum = 0.0;
            for (std::size_t q = 0; q < radix; ++q) {
                const double angle =
                    sign * 2.0 * PI * static_cast<double>(q * k)
                    / static_cast<double>(N);

                std::complex<double> w(std::cos(angle), std::sin(angle));
                sum += array_parts[q][i] * w;
            }

            array[k] = sum;
        }
    }
}

std::vector<std::complex<double>> FFT::fft(
    const std::vector<std::complex<double>>& signal
) const {
    check_length(signal.size());

    std::vector<std::complex<double>> spectrum = signal;
    transform(spectrum, false);
    return spectrum;
}

std::vector<std::complex<double>> FFT::ifft(
    const std::vector<std::complex<double>>& spectrum
) const {
    check_length(spectrum.size());

    std::vector<std::complex<double>> signal = spectrum;
    transform(signal, true);
    for (std::complex<double>& value : signal) {
        value /= static_cast<double>(spectrum.size());
    }
    return signal;

}
