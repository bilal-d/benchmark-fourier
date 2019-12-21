// SPDX-License-Identifier: MIT
// Copyright © 2019  Bilal Djelassi

#include "custom_complex.hpp"
#include <iostream>

std::ostream&
operator<<(std::ostream& out, fcomplex_t const& z)
{
    return out << "(" << z.real << "," << z.imag << ")";
}
