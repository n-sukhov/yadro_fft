#include "fft.h"
#include "utils.h"

#include <algorithm>
#include <cmath>
#include <complex>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

const std::string input_dir = "data/input";
const std::string spectrum_dir = "data/spectrum";
const std::string output_dir = "data/output";

int main(int argc, char** argv) {
    std::size_t N;
    if (argc == 2) N = std::stoi(argv[1]);
    else N = 36000;

    ensure_data_dir(input_dir);
    ensure_data_dir(spectrum_dir);
    ensure_data_dir(output_dir);

    FFT fft;

    std::mt19937 generator(42);
    std::uniform_real_distribution<double> distribution(-1.0, 1.0);

    std::vector<std::complex<double>> input_signal(N);

    for (std::size_t i = 0; i < N; ++i) {
        const double real = distribution(generator);
        const double imag = distribution(generator);

        input_signal[i] = std::complex<double>(real, imag);
    }
    csv_write(input_dir + "/N_" + std::to_string(N) + "_input_signal.csv", input_signal);

    std::vector<std::complex<double>> spectrum = fft.fft(input_signal);
    csv_write(spectrum_dir + "/N_" + std::to_string(N) + "_spectrum.csv", spectrum);

    std::vector<std::complex<double>> output_signal = fft.ifft(spectrum);
    csv_write(output_dir + "/N_" + std::to_string(N) + "_output_signal.csv", output_signal);

    double max_abs_error = 0.0;
    double err_sum = 0.0;
    for (std::size_t i = 0; i < N; ++i) {
        double error = std::abs(output_signal[i] - input_signal[i]);
        err_sum += error;
        if (error > max_abs_error) {
            max_abs_error = error;
        }
    }
    double mean_abs_error = err_sum / N;

    std::cout << std::setprecision(9);

    std::cout << "FFT length N = " << N << "\n";
    std::cout << "MAE = " << mean_abs_error << "\n";
    std::cout << "Max absolute error = " << max_abs_error << "\n";

    return 0;
}