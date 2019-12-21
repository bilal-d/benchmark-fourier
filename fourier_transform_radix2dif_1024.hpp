// SPDX-License-Identifier: MIT
// Copyright © 2019  Bilal Djelassi

#pragma once
#include <complex>

void
fourier_transform_radix2dif(
    std::complex<float> const (&)[1024],
    std::complex<float> (&)[1024]);
