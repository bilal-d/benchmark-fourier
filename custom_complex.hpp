// SPDX-License-Identifier: MIT
// Copyright © 2019  Bilal Djelassi

#pragma once
#include <complex>
#include <iosfwd>

struct fcomplex_t
{
    float real;
    float imag;

    fcomplex_t&
    operator=(std::complex<float> const& z)
    {
        real = z.real();
        imag = z.imag();
        return *this;
    }
};

inline fcomplex_t
operator+(fcomplex_t const& z1, fcomplex_t const& z2)
{
    return { z1.real + z2.real, z1.imag + z2.imag };
}

inline fcomplex_t
operator-(fcomplex_t const& z1, fcomplex_t const& z2)
{
    return { z1.real - z2.real, z1.imag - z2.imag };
}

inline fcomplex_t
operator*(fcomplex_t const& z1, fcomplex_t const& z2)
{
    return {
        z1.real * z2.real - z1.imag * z2.imag,
        z1.real * z2.imag + z1.imag * z2.real
    };
}

inline fcomplex_t&
operator+=(fcomplex_t& z1, fcomplex_t const& z2)
{
    z1.real += z2.real;
    z1.imag += z2.imag;
    return z1;
}

inline fcomplex_t&
operator-=(fcomplex_t& z1, fcomplex_t const& z2)
{
    z1.real -= z2.real;
    z1.imag -= z2.imag;
    return z1;
}

inline fcomplex_t&
operator*=(fcomplex_t& z1, fcomplex_t const& z2)
{
    float ac = z1.real * z2.real;
    float bd = z1.imag * z2.imag;
    float ad = z1.real * z2.imag;
    float bc = z1.imag * z2.real;

    z1.real = ac - bd;
    z1.imag = bc + ad;
    return z1;
}

inline fcomplex_t
operator-(fcomplex_t const& z)
{
    return { -z.real, -z.imag };
}

inline fcomplex_t
operator!(fcomplex_t const& z)
{
    return { z.imag, -z.real };
}

std::ostream&
operator<<(std::ostream& out, fcomplex_t const& z);

