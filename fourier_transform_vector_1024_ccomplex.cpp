// SPDX-License-Identifier: MIT
// Copyright © 2019  Bilal Djelassi

#include "custom_complex.hpp"

namespace {

// Tableau de 1024 valeurs complexes servant à implémenter une
// transformée de Fourier sur 1024 points.
// Les éléments de ce tableau sont donnés par
// w[r] = exp(-i*2*pi*r/1024).

fcomplex_t constexpr w[1024] = {
#include "fourier_vector_1024.inc"
};

} // namespace


void
fourier_transform_vector(
    fcomplex_t const (&x)[1024],
    fcomplex_t (&y)[1024])
{
    for (unsigned int i = 0; i < 1024; ++i) {
        y[i] = fcomplex_t{0.0f, 0.0f};

        for (unsigned int j = 0; j < 1024; ++j)
            y[i] = y[i] + w[(i*j) % 1024] * x[j];
    }
}
