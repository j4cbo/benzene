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

#include <cinttypes>
#include <iostream>

namespace benzene {

class Q8_24 {
    /*
     * Q8_24 encodes a fixed-point value in Q8_24 format. This is a signed format that
     * represents the range [-128.0, 128.0) with a 32-bit number.
     */

public:
    static constexpr int MANTISSA_BITS = 24;
    static constexpr double MULTIPLIER = (1 << MANTISSA_BITS);

    constexpr Q8_24() : v(0) {}
    constexpr explicit Q8_24(double d) : v(int32_t(d * MULTIPLIER)) {}

    /* +, -, % need no adjustment. */
    constexpr Q8_24 operator+(const Q8_24 & rhs) const { return Q8_24(from_raw{}, v + rhs.v); }
    constexpr Q8_24 operator-(const Q8_24 & rhs) const { return Q8_24(from_raw{}, v - rhs.v); }
    constexpr Q8_24 operator%(const Q8_24 & rhs) const { return Q8_24(from_raw{}, v % rhs.v); }

    constexpr Q8_24 operator*(const Q8_24 & rhs) const {
        int64_t product = int64_t(int32_t(v)) * int64_t(int32_t(rhs.v));
        return Q8_24(from_raw{}, product >> MANTISSA_BITS);
    }

    constexpr Q8_24 operator/(const Q8_24 & rhs) const {
        int64_t div = (int64_t(int32_t(v)) << MANTISSA_BITS) / int64_t(int32_t(rhs.v));
        return Q8_24(from_raw{}, div);
    }

    /* Relational comparisons can just operate on the representation directly */
    constexpr bool operator==(const Q8_24 & rhs) const { return v == rhs.v; }
    constexpr bool operator!=(const Q8_24 & rhs) const { return v != rhs.v; }
    constexpr bool operator>=(const Q8_24 & rhs) const { return int32_t(v) >= int32_t(rhs.v); }
    constexpr bool operator>(const Q8_24 & rhs)  const { return int32_t(v) > int32_t(rhs.v); }
    constexpr bool operator<(const Q8_24 & rhs)  const { return int32_t(v) < int32_t(rhs.v); }
    constexpr bool operator<=(const Q8_24 & rhs) const { return int32_t(v) <= int32_t(rhs.v); }

    constexpr double as_double() const { return int32_t(v) / MULTIPLIER; }

    constexpr int16_t as_q0_15() const {
        return int32_t(v) >> 9;
    }

    constexpr int16_t as_q8() const {
        return v >> 16;
    }

    constexpr Q8_24 saturate_normal() const {
        if (*this > normal_max()) {
            return normal_max();
        } else if (*this < normal_min()) {
            return normal_min();
        } else {
            return *this;
        }
    }

    constexpr Q8_24 saturate_positive_normal() const {
        if (*this > normal_max()) {
            return normal_max();
        } else if (*this < Q8_24(0)) {
            return Q8_24(0);
        } else {
            return *this;
        }
    }

    static constexpr Q8_24 normal_max() {
        return Q8_24(from_raw{}, (1 << MANTISSA_BITS) - 1);
    }

    static constexpr Q8_24 normal_min() {
        return Q8_24(-1);
    }

    static constexpr Q8_24 epsilon() {
        return Q8_24(from_raw{}, 1);
    }

private:
    struct from_raw {};
    constexpr Q8_24(from_raw, uint32_t v) : v(v) {}
    uint32_t v;
};

inline std::ostream & operator<< (std::ostream & os, const Q8_24 & val) {
    os << val.as_double();
    return os;
}

} // namespace benzene
