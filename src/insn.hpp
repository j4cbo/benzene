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

namespace benzene {

struct Insn {

    enum class T : char {
        ADD_RR,
        ADD_RC,
        SUB_RR,
        SUB_RC,
        SUB_CR,
        MUL_RR,
        MUL_RC,
        DIV_RR,
        DIV_RC,
        DIV_CR,
        MOD_RR,
        MOD_RC,
        SIN,
        SIN2PI,
        COS,
        COS2PI,
        CONST
    };

    T opcode;
    uint8_t x;
    uint8_t y;
    uint8_t z;

    Insn(T opcode, uint8_t x, uint8_t y, uint8_t z)
        : opcode(opcode), x(x), y(y), z(z) {}
};

}
