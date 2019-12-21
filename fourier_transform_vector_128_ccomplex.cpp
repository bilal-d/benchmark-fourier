// SPDX-License-Identifier: MIT
// Copyright © 2019  Bilal Djelassi

#include "custom_complex.hpp"

namespace {

// Tableau de 128 valeurs complexes servant à implémenter une
// transformée de Fourier sur 128 points.
// Les éléments de ce tableau sont donnés par
// w[r] = exp(-i*2*pi*r/128).

fcomplex_t constexpr w[128] = {
#include "fourier_vector_128.inc"
};

} // namespace


void
fourier_transform_vector(
    fcomplex_t const (&x)[128],
    fcomplex_t (&y)[128])
{
    for (unsigned int i = 0; i < 128; ++i) {
        y[i] = fcomplex_t{0.0f, 0.0f};

        for (unsigned int j = 0; j < 128; ++j)
            y[i] = y[i] + w[(i*j) % 128] * x[j];
    }
}
