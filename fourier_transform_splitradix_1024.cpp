// SPDX-License-Identifier: MIT
// Copyright © 2019  Bilal Djelassi

#include <complex>

namespace {

std::complex<float> constexpr w[] = {
#include "fourier_splitradix_twiddle_1024.inc"
};

inline std::complex<float>
operator!(std::complex<float> const& z)
{
    return { z.imag(), -z.real() };
}

template<unsigned int n, unsigned int s>
inline void
fourier_transform_splitradix_recurse(
    std::complex<float> const* x,
    std::complex<float>* y)
{
    static_assert(n * s == 1024);

    if constexpr (n == 2) {
        std::complex<float> t0, t1;

        t0 = x[0];
        t1 = x[s];

        y[0] = t0 + t1;
        y[1] = t0 - t1;
    }
    else if constexpr (n == 4) {
        std::complex<float> t0, t1, t2, t3;

        t0 = x[0] + x[2*s];
        t1 = x[0] - x[2*s];
        t2 = x[s] + x[3*s];
        t3 = !(x[s] - x[3*s]);

        y[0] = t0 + t2;
        y[1] = t1 + t3;
        y[2] = t0 - t2;
        y[3] = t1 - t3;
    }
    else {
        fourier_transform_splitradix_recurse<n/2, 2*s>(x, y);
        fourier_transform_splitradix_recurse<n/4, 4*s>(x + s, y + n/2);
        fourier_transform_splitradix_recurse<n/4, 4*s>(x + s + 2*s, y + n/2 + n/4);

        for (unsigned int k = 0; k < n/4; ++k) {
            std::complex<float> t0, t1;

            t0 = y[k + n/2] * w[k*s];
            t1 = y[k + n/2 + n/4] * w[3*k*s];

            y[k + n/2] = t0 + t1;
            y[k + n/2 + n/4] = !(t0 - t1);
        }
        for (unsigned int k = 0; k < n/2; ++k) {
            std::complex<float> t0, t1;

            t0 = y[k];
            t1 = y[k + n/2];

            y[k]        = t0 + t1;
            y[k + n/2]  = t0 - t1;
        }
    }
}

} // namespace

void
fourier_transform_splitradix(
    std::complex<float> const (&x)[1024],
    std::complex<float> (&y)[1024])
{
    fourier_transform_splitradix_recurse<1024, 1>(x, y);
}
