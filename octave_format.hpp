// SPDX-License-Identifier: MIT
// Copyright © 2019  Bilal Djelassi

#pragma once
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <type_traits>


template<typename complex_t>
struct octave_format {
    std::string name;
    complex_t const* values;
    unsigned int size;

    template<unsigned int size>
    octave_format(
        std::string const& name,
        complex_t const (&values)[size])
    : name(name), values(values), size(size)
    {}

    octave_format(
        std::string const& name,
        complex_t const* values,
        unsigned int size)
    : name(name), values(values), size(size)
    {}
};

template<typename complex_t>
inline std::ostream&
operator<<(
    std::ostream& out,
    octave_format<complex_t> const& data)
{
    out << "# name: " << data.name << "\n"
        << "# type: complex matrix\n"
        << "# rows: " << data.size << "\n"
        << "# columns: 1\n";

    using fptype = std::conditional_t<sizeof(complex_t) == 2*sizeof(float), float, double>;
    constexpr int digits = std::numeric_limits<fptype>::max_digits10;

    auto const old_precision = out.precision(digits);
    for (unsigned int i = 0; i < data.size; ++i)
        out << data.values[i] << "\n";

    out.precision(old_precision);
    return out;
}

template<typename complex_t>
inline void
save_octave_format(
    std::string const& file,
    octave_format<complex_t> const& data)
{
    std::ofstream out;
    out.open(file, std::ios::out | std::ios::binary);
    if (!out.is_open())
        throw std::runtime_error(
            "could not open '" + file + "' in write mode");

    out << data;
    out.close();

    if (!out.good())
        throw std::runtime_error(
            "error while writing data to '" + file +"'");
}
