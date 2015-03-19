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
#include "color.hpp"

namespace benzene {

struct Point {
    Q8_24 x;
    Q8_24 y;
    Color color;

    constexpr Point(double x, double y, const Color & color) : x(x), y(y), color(color) {}
    constexpr Point(Q8_24 x, Q8_24 y, const Color & color) : x(x), y(y), color(color) {}

    bool operator==(const Point & other) const {
        return x == other.x && y == other.y && color == other.color;
    }
    bool operator!=(const Point & other) const {
        return !(*this == other);
    }
};

inline std::ostream & operator<< (std::ostream & os, const Point & val) {
    os << "{ " << val.x << ", " << val.y << ", " << val.color << " }";
    return os;
}

} // namespace benzene
