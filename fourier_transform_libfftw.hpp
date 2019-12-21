// SPDX-License-Identifier: MIT
// Copyright © 2019  Bilal Djelassi

#pragma once
#include <memory>
#include <functional>
#include <complex>

class fourier_transform_libfftw {
    struct implementation;
    std::unique_ptr<implementation> impl;

    fourier_transform_libfftw(fourier_transform_libfftw const&) = delete;
    fourier_transform_libfftw& operator=(fourier_transform_libfftw const&) = delete;

public:
    fourier_transform_libfftw(unsigned int size, bool aligned);
    ~fourier_transform_libfftw();

    std::complex<float>* x();
    std::complex<float>* y();
    unsigned int size();
    void operator()();

    using routine_t = std::reference_wrapper<fourier_transform_libfftw>;
};

