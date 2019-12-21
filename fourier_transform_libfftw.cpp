// SPDX-License-Identifier: MIT
// Copyright © 2019  Bilal Djelassi

#include "fourier_transform_libfftw.hpp"
#include <fftw3.h>
#include <complex>
#include <stdexcept>

struct fourier_transform_libfftw::implementation {
    unsigned int size;
    fftwf_complex* x_ptr;
    fftwf_complex* y_ptr;
    fftwf_plan plan;

    implementation(unsigned int size, bool aligned) :
        size(size),
        x_ptr(nullptr),
        y_ptr(nullptr),
        plan(nullptr)
    {
        x_ptr = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * size);
        if (!x_ptr) {
            cleanup();
            throw std::runtime_error("cannot allocate input array");
        }

        y_ptr = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * size);
        if (!y_ptr) {
            cleanup();
            throw std::runtime_error("cannot allocate output array");
        }

        unsigned int flags = FFTW_PRESERVE_INPUT;
        if (!aligned)
            flags |= FFTW_UNALIGNED;

        plan = fftwf_plan_dft_1d(size, x_ptr, y_ptr, FFTW_FORWARD, flags);
        if (!plan) {
            cleanup();
            throw std::runtime_error("cannot initialize fftw plan");
        }
    }

    void cleanup() {
        if (plan)
            fftwf_destroy_plan(plan);
        if (y_ptr)
            fftwf_free(y_ptr);
        if (x_ptr)
            fftwf_free(x_ptr);
    }

    ~implementation() {
        cleanup();
    }
};

fourier_transform_libfftw::fourier_transform_libfftw(unsigned int size, bool aligned)
    : impl(std::make_unique<implementation>(size, aligned))
{}

fourier_transform_libfftw::~fourier_transform_libfftw()
{}

unsigned int fourier_transform_libfftw::size()
{
    return impl->size;
}

std::complex<float>* fourier_transform_libfftw::x()
{
    return reinterpret_cast<std::complex<float>*>(impl->x_ptr);
}

std::complex<float>* fourier_transform_libfftw::y()
{
    return reinterpret_cast<std::complex<float>*>(impl->y_ptr);
}

void fourier_transform_libfftw::operator()()
{
    fftwf_execute(impl->plan);
}
