// SPDX-License-Identifier: MIT
// Copyright © 2019  Bilal Djelassi

#include "custom_complex.hpp"
#include "octave_format.hpp"
#include "fourier_transform_libfftw.hpp"
#include "fourier_transform_vector_128.hpp"
#include "fourier_transform_radix2dit_128.hpp"
#include "fourier_transform_radix2dif_128.hpp"
#include "fourier_transform_splitradix_128.hpp"
#include "fourier_transform_vector_1024.hpp"
#include "fourier_transform_radix2dit_1024.hpp"
#include "fourier_transform_radix2dif_1024.hpp"
#include "fourier_transform_splitradix_1024.hpp"
#include "fourier_transform_vector_128_ccomplex.hpp"
#include "fourier_transform_radix2dit_128_ccomplex.hpp"
#include "fourier_transform_radix2dif_128_ccomplex.hpp"
#include "fourier_transform_splitradix_128_ccomplex.hpp"
#include "fourier_transform_vector_1024_ccomplex.hpp"
#include "fourier_transform_radix2dit_1024_ccomplex.hpp"
#include "fourier_transform_radix2dif_1024_ccomplex.hpp"
#include "fourier_transform_splitradix_1024_ccomplex.hpp"

#include <algorithm>
#include <chrono>
#include <complex>
#include <functional>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

namespace {

struct measure_result {
    std::chrono::nanoseconds minimum;
    std::chrono::nanoseconds maximum;
    std::chrono::nanoseconds average;
};

measure_result
measure(
    std::function<void()> routine,
    unsigned int repeat,
    unsigned int rounds,
    unsigned int outliers)
{
    using std::chrono::nanoseconds;
    using std::chrono::steady_clock;
    using std::chrono::duration_cast;

    std::vector<nanoseconds> measures(
        rounds + outliers,
        nanoseconds::zero());

    for (auto& measure : measures) {
        auto start = steady_clock::now();

        for (unsigned int i = 0; i < repeat; ++i)
            routine();

        auto end = steady_clock::now();
        measure = duration_cast<nanoseconds>(end - start);
    }

    std::sort(std::begin(measures), std::end(measures));
    measures.resize(rounds);

    auto minimum = measures.front() / repeat;
    auto maximum = measures.back() / repeat;
    auto average = std::reduce(
        std::begin(measures),
        std::end(measures)
    ) / (repeat * measures.size()) ;

    return { minimum, maximum, average };
}

std::ostream&
operator<<(std::ostream& out, measure_result const& result)
{
    struct stream_state {
        std::ostream& out;
        std::ios::fmtflags flags;
        explicit stream_state(std::ostream& out)
            : out(out), flags(out.flags()) {}
        ~stream_state() { out.flags(flags); }
    } save(out);

    using std::setw;
    using std::setprecision;
    using std::fixed;

    double minimum = result.minimum.count() / 1000.0;
    double maximum = result.maximum.count() / 1000.0;
    double average = result.average.count() / 1000.0;
    double max_percent = 100.0 * result.maximum / result.minimum;
    double avg_percent = 100.0 * result.average / result.minimum;

    return out
        << fixed
        << "    minimum: "
        << setprecision(3) << setw(8) << minimum << " µs\n"
        << "    maximum: "
        << setprecision(3) << setw(8) << maximum << " µs "
        << "(" << setprecision(1) << setw(5) << max_percent << "% of minimum)\n"
        << "    average: "
        << setprecision(3) << setw(8) << average << " µs "
        << "(" << setprecision(1) << setw(5) << avg_percent << "% of minimum)\n";
}

} // namespace


int main()
{
    using fourier_routine_128_t =
        void (*)(std::complex<float> const (&)[128], std::complex<float> (&)[128]);
    using fourier_routine_1024_t =
        void (*)(std::complex<float> const (&)[1024], std::complex<float> (&)[1024]);
    using fourier_routine_128_ccomplex_t =
        void (*)(fcomplex_t const (&)[128], fcomplex_t (&)[128]);
    using fourier_routine_1024_ccomplex_t =
        void (*)(fcomplex_t const (&)[1024], fcomplex_t (&)[1024]);

    using fourier_routine_variant_t = std::variant<
        fourier_routine_128_t,
        fourier_routine_1024_t,
        fourier_routine_128_ccomplex_t,
        fourier_routine_1024_ccomplex_t,
        fourier_transform_libfftw::routine_t>;

    fourier_transform_libfftw fourier_transform_libfftw_128(128, false);
    fourier_transform_libfftw fourier_transform_libfftw_1024(1024, false);
    fourier_transform_libfftw fourier_transform_libfftw_128_aligned(128, true);
    fourier_transform_libfftw fourier_transform_libfftw_1024_aligned(1024, true);

    struct {
        std::string name;
        unsigned int repeat;
        unsigned int rounds;
        unsigned int outliers;
        fourier_routine_variant_t routine;
    } const tests[] = {
        { "vector_128",      100, 100, 10,
            (fourier_routine_128_t)&fourier_transform_vector },
        { "radix2dit_128",  1000, 100, 10,
            (fourier_routine_128_t)&fourier_transform_radix2dit },
        { "radix2dif_128",  1000, 100, 10,
            (fourier_routine_128_t)&fourier_transform_radix2dif },
        { "splitradix_128", 1000, 100, 10,
            (fourier_routine_128_t)&fourier_transform_splitradix },

        { "vector_1024",      20,  20,  2,
            (fourier_routine_1024_t)&fourier_transform_vector },
        { "radix2dit_1024",  100, 100, 10,
            (fourier_routine_1024_t)&fourier_transform_radix2dit },
        { "radix2dif_1024",  100, 100, 10,
            (fourier_routine_1024_t)&fourier_transform_radix2dif },
        { "splitradix_1024", 100, 100, 10,
            (fourier_routine_1024_t)&fourier_transform_splitradix },

        { "vector_128_ccomplex",      100, 100, 10,
            (fourier_routine_128_ccomplex_t)&fourier_transform_vector },
        { "radix2dit_128_ccomplex",  1000, 100, 10,
            (fourier_routine_128_ccomplex_t)&fourier_transform_radix2dit },
        { "radix2dif_128_ccomplex",  1000, 100, 10,
            (fourier_routine_128_ccomplex_t)&fourier_transform_radix2dif },
        { "splitradix_128_ccomplex", 1000, 100, 10,
            (fourier_routine_128_ccomplex_t)&fourier_transform_splitradix },

        { "vector_1024_ccomplex",      20,  20,  2,
            (fourier_routine_1024_ccomplex_t)&fourier_transform_vector },
        { "radix2dit_1024_ccomplex",  100, 100, 10,
            (fourier_routine_1024_ccomplex_t)&fourier_transform_radix2dit },
        { "radix2dif_1024_ccomplex",  100, 100, 10,
            (fourier_routine_1024_ccomplex_t)&fourier_transform_radix2dif },
        { "splitradix_1024_ccomplex", 100, 100, 10,
            (fourier_routine_1024_ccomplex_t)&fourier_transform_splitradix },

        { "libfftw_128",         1000, 100, 10, fourier_transform_libfftw_128 },
        { "libfftw_1024",         100, 100, 10, fourier_transform_libfftw_1024 },
        { "libfftw_128_aligned", 1000, 100, 10, fourier_transform_libfftw_128_aligned },
        { "libfftw_1024_aligned", 100, 100, 10, fourier_transform_libfftw_1024_aligned },
    };

    std::random_device rdev;
    std::normal_distribution<float> ndist{0.0f, 1.0f};

    std::complex<float> x1[128];
    fcomplex_t x1_ccomplex[128];
    std::generate(std::begin(x1), std::end(x1), [&](){
        float real = ndist(rdev);
        float imag = ndist(rdev);
        return std::complex<float>{real, imag};
    });
    std::copy(std::begin(x1), std::end(x1), std::begin(x1_ccomplex));
    std::copy(std::begin(x1), std::end(x1), fourier_transform_libfftw_128.x());
    std::copy(std::begin(x1), std::end(x1), fourier_transform_libfftw_128_aligned.x());

    save_octave_format<std::complex<float>>(
        "x_128.mat", {"x_128", x1});

    std::complex<float> x2[1024];
    fcomplex_t x2_ccomplex[1024];
    std::generate(std::begin(x2), std::end(x2), [&](){
        float real = ndist(rdev);
        float imag = ndist(rdev);
        return std::complex<float>{real, imag};
    });
    std::copy(std::begin(x2), std::end(x2), std::begin(x2_ccomplex));
    std::copy(std::begin(x2), std::end(x2), fourier_transform_libfftw_1024.x());
    std::copy(std::begin(x2), std::end(x2), fourier_transform_libfftw_1024_aligned.x());

    save_octave_format<std::complex<float>>("x_1024.mat", {"x_1024", x2});

    std::complex<float> y1[128];
    fcomplex_t y1_ccomplex[128];
    std::complex<float> y2[1024];
    fcomplex_t y2_ccomplex[1024];

    for (auto const& test : tests) {
        std::cout << test.name << "\n";

        std::visit([&](auto const& routine){
            using routine_type = std::decay_t<decltype(routine)>;

            if constexpr (std::is_same_v<routine_type, fourier_routine_128_t>) {
                std::fill(std::begin(y1), std::end(y1), std::complex<float>{0.0f, 0.0f});

                measure_result result = measure([&](){
                    routine(x1, y1);
                }, test.repeat, test.rounds, test.outliers);

                save_octave_format<std::complex<float>>(
                    "y_" + test.name + ".mat", {"y_" + test.name, y1});

                std::cout << result << "\n";
            }

            if constexpr (std::is_same_v<routine_type, fourier_routine_1024_t>) {
                std::fill(std::begin(y2), std::end(y2), std::complex<float>{0.0f, 0.0f});

                measure_result result = measure([&](){
                    routine(x2, y2);
                }, test.repeat, test.rounds, test.outliers);

                save_octave_format<std::complex<float>>(
                    "y_" + test.name + ".mat", {"y_" + test.name, y2});

                std::cout << result << "\n";
            }

            if constexpr (std::is_same_v<routine_type, fourier_routine_128_ccomplex_t>) {
                std::fill(std::begin(y1_ccomplex), std::end(y1_ccomplex), fcomplex_t{0.0f, 0.0f});

                measure_result result = measure([&](){
                    routine(x1_ccomplex, y1_ccomplex);
                }, test.repeat, test.rounds, test.outliers);

                save_octave_format<fcomplex_t>(
                    "y_" + test.name + ".mat", {"y_" + test.name, y1_ccomplex});

                std::cout << result << "\n";
            }

            if constexpr (std::is_same_v<routine_type, fourier_routine_1024_ccomplex_t>) {
                std::fill(std::begin(y2_ccomplex), std::end(y2_ccomplex), fcomplex_t{0.0f, 0.0f});

                measure_result result = measure([&](){
                    routine(x2_ccomplex, y2_ccomplex);
                }, test.repeat, test.rounds, test.outliers);

                save_octave_format<fcomplex_t>(
                    "y_" + test.name + ".mat", {"y_" + test.name, y2_ccomplex});

                std::cout << result << "\n";
            }

            if constexpr (std::is_same_v<routine_type, fourier_transform_libfftw::routine_t>) {
                std::fill_n(routine.get().y(), routine.get().size(), std::complex<float>{0.0f, 0.0f});

                measure_result result = measure(routine,
                    test.repeat, test.rounds, test.outliers);

                save_octave_format<std::complex<float>>(
                    "y_" + test.name + ".mat", {"y_" + test.name, routine.get().y(), routine.get().size()});

                std::cout << result << "\n";
            }
        }, test.routine);
    }
}
