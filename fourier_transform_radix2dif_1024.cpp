// SPDX-License-Identifier: MIT
// Copyright © 2019  Bilal Djelassi

#include <complex>

namespace {

std::complex<float> constexpr w[] = {
#include "fourier_radix2dif_twiddle_1024.inc"
};

unsigned int constexpr r[][2] = {
#include "fourier_radix2dif_reorder_1024.inc"
};

template<unsigned int n, unsigned int s>
inline void
fourier_transform_radix2dif_recurse(
    std::complex<float> const* x,
    std::complex<float>* y)
{
    static_assert(n * s == 1024);

    if constexpr (n == 2) {
        std::complex<float> t0, t1;
        t0 = x[0];
        t1 = x[1];
        y[0] = t0 + t1;
        y[1] = t0 - t1;
    }
    else {
        for (unsigned int k = 0; k < n/2; ++k) {
            std::complex<float> t0, t1;
            t0 = x[k];
            t1 = x[k + n/2];
            y[k] = t0 + t1;
            y[k + n/2] = (t0 - t1) * w[k*s];
        }

        fourier_transform_radix2dif_recurse<n/2, 2*s>(y, y);
        fourier_transform_radix2dif_recurse<n/2, 2*s>(y+n/2, y+n/2);
    }
}

} // namespace

void
fourier_transform_radix2dif(
    std::complex<float> const (&x)[1024],
    std::complex<float> (&y)[1024])
{
    fourier_transform_radix2dif_recurse<1024, 1>(x, y);

    for (auto const [j, k] : r) {
        std::complex<float> t = y[j];
        y[j] = y[k];
        y[k] = t;
    }
}
