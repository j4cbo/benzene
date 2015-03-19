#pragma once

/*
 * benzene laser synthesis library
 * Copyright (c) 2015 Jacob Potter, All rights reserved.
 *
 * This library is free software; you can redistribute it and/or modify it under the terms of
 * the GNU Lesser General Public License as published by the Free Software Foundation,
 * version 2.1.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * The License can be found in lgpl-2.1.txt or at https://www.gnu.org/licenses/lgpl-2.1.html
 */

#include "q8_24.hpp"

namespace benzene {

struct Color {
    Q8_24 r;
    Q8_24 g;
    Q8_24 b;

    constexpr Color(Q8_24 r, Q8_24 g, Q8_24 b) : r(r), g(g), b(b) {}
    constexpr Color(double r, double g, double b) : r(r), g(g), b(b) {}

    constexpr bool operator==(const Color & other) const {
        return r == other.r && g == other.g && b == other.b;
    }
    bool operator!=(const Color & other) const {
        return !(*this == other);
    }
};

inline std::ostream & operator<< (std::ostream & os, const Color & val) {
    os << "{ " << val.r << ", " << val.g << ", " << val.b << " }";
    return os;
}

} // namespace benzene
