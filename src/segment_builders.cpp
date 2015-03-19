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

#include "segment.hpp"
#include "color.hpp"
#include "insn.hpp"

namespace benzene {

Segment make_line_segment(double x1, double y1, double x2, double y2, const Color & color) {

    // For a line from x1, y1 to x2, y2, we have:
    // x = x1 + (x2-x1) * tSeg
    // y = y1 + (y2-y1) * tSeg

    return Segment(
        {
            { Insn::T::MUL_RC, 10, 0, 0 },
            { Insn::T::ADD_RC, 0, 1, 0 },
            { Insn::T::MUL_RC, 10, 2, 1 },
            { Insn::T::ADD_RC, 1, 3, 1 },
            { Insn::T::CONST, 4, 0, 2 },
            { Insn::T::CONST, 5, 0, 3 },
            { Insn::T::CONST, 6, 0, 4 },
        }, {
            Q8_24(x2) - Q8_24(x1),
            Q8_24(x1),
            Q8_24(y2) - Q8_24(y1),
            Q8_24(y1),
            color.r,
            color.g,
            color.b
        }
    );
}

Segment make_circle_segment(double x1, double y1, double r, const Color & color) {

    return Segment(
        {
            { Insn::T::SIN2PI, 10, 0, 9 },
            { Insn::T::MUL_RC, 9, 0, 0 },
            { Insn::T::ADD_RC, 0, 1, 0 },
            { Insn::T::COS2PI, 10, 0, 9 },
            { Insn::T::MUL_RC, 9, 0, 1 },
            { Insn::T::ADD_RC, 1, 2, 1 },
            { Insn::T::CONST, 3, 0, 2 },
            { Insn::T::CONST, 4, 0, 3 },
            { Insn::T::CONST, 5, 0, 4 },
        }, {
            Q8_24(r),
            Q8_24(x1),
            Q8_24(y1),
            color.r,
            color.g,
            color.b
        }
    );
}

} // namespace benzene
