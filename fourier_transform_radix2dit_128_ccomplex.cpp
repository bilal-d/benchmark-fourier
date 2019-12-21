// SPDX-License-Identifier: MIT
// Copyright © 2019  Bilal Djelassi

#include "custom_complex.hpp"

namespace {

fcomplex_t constexpr w[] = {
#include "fourier_radix2dit_twiddle_128.inc"
};

template<unsigned int n, unsigned int s>
inline void
fourier_transform_radix2dit_recurse(
    fcomplex_t const* x,
    fcomplex_t* y)
{
    static_assert(n * s == 128);

    if constexpr (n == 2) {
        fcomplex_t t0, t1;
        t0 = x[0];
        t1 = x[s];
        y[0] = t0 + t1;
        y[1] = t0 - t1;
    }
    else {
        fourier_transform_radix2dit_recurse<n/2, 2*s>(x, y);
        fourier_transform_radix2dit_recurse<n/2, 2*s>(x+s, y+n/2);

        for (unsigned int k = 0; k < n/2; ++k) {
            fcomplex_t t0, t1;
            t0 = y[k];
            t1 = y[k + n/2] * w[k*s];
            y[k] = t0 + t1;
            y[k + n/2] = t0 - t1;
        }
    }
}

} // namespace

void
fourier_transform_radix2dit(
    fcomplex_t const (&x)[128],
    fcomplex_t (&y)[128])
{
    fourier_transform_radix2dit_recurse<128, 1>(x, y);
}
