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

#include <vector>
#include "point.hpp"

namespace benzene {

struct Insn;
struct Color;
class Q8_24;

class Segment final {
public:
    Segment(std::vector<Insn> insns, std::vector<Q8_24> consts);
    Segment(const Segment &);
    Segment(Segment &&);
    ~Segment();

    /*
     * Evaluate this segment at a given (tSeg, tFrame)
     */
    Point eval(Q8_24 tSeg, Q8_24 tFrame) const;
    Point eval(double tSeg, double tFrame) const { return eval(Q8_24(tSeg), Q8_24(tFrame)); }

private:
    std::vector<Insn> insns;
    std::vector<Q8_24> consts;
};

} // namespace benzene
