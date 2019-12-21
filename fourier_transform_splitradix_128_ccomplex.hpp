// SPDX-License-Identifier: MIT
// Copyright © 2019  Bilal Djelassi

#pragma once
#include "custom_complex.hpp"

void
fourier_transform_splitradix(
    fcomplex_t const (&)[128],
    fcomplex_t (&)[128]);
