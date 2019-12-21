// SPDX-License-Identifier: MIT
// Copyright © 2019  Bilal Djelassi

#pragma once
#include "custom_complex.hpp"

void
fourier_transform_radix2dit(
    fcomplex_t const (&)[1024],
    fcomplex_t (&)[1024]);
