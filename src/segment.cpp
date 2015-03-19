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

#include <array>
#include <cmath>

namespace benzene {

Segment::Segment(const Segment &) = default;
Segment::Segment(Segment &&) = default;
Segment::~Segment() = default;

Segment::Segment(std::vector<Insn> insns, std::vector<Q8_24> consts)
    : insns(move(insns)), consts(move(consts)) {}

class RegisterFile {
public:
    RegisterFile() {}

    Q8_24 & operator[](int reg) {
        return regs.at(reg);
    }

    static constexpr int REG_MAX = 12;

    void dump() {
        for (const auto & r : regs) {
            std::cout << r << " ";
        }
        std::cout << "\n";
    }

private:
    std::array<Q8_24, REG_MAX> regs = {};
};

Point Segment::eval(Q8_24 tSeg, Q8_24 tFrame) const {

    RegisterFile rf;
    rf[10] = tSeg;
    rf[11] = tFrame;

    for (const Insn & insn : insns) {
        switch (insn.opcode) {
        case Insn::T::ADD_RR:
            rf[insn.z] = rf[insn.x] + rf[insn.y];
            break;
        case Insn::T::ADD_RC:
            rf[insn.z] = rf[insn.x] + consts.at(insn.y);
            break;
        case Insn::T::SUB_RR:
            rf[insn.z] = rf[insn.x] - rf[insn.y];
            break;
        case Insn::T::SUB_RC:
            rf[insn.z] = rf[insn.x] - consts.at(insn.y);
            break;
        case Insn::T::SUB_CR:
            rf[insn.z] = consts.at(insn.x) - rf[insn.y];
            break;
        case Insn::T::MUL_RR:
            rf[insn.z] = rf[insn.x] * rf[insn.y];
            break;
        case Insn::T::MUL_RC:
            rf[insn.z] = rf[insn.x] * consts.at(insn.y);
            break;
        case Insn::T::DIV_RR:
            rf[insn.z] = rf[insn.x] / rf[insn.y];
            break;
        case Insn::T::DIV_RC:
            rf[insn.z] = rf[insn.x] / consts.at(insn.y);
            break;
        case Insn::T::DIV_CR:
            rf[insn.z] = consts.at(insn.x) / rf[insn.y];
            break;
        case Insn::T::MOD_RR:
            rf[insn.z] = rf[insn.x] % rf[insn.y];
            break;
        case Insn::T::MOD_RC:
            rf[insn.z] = rf[insn.x] % consts.at(insn.y);
            break;
        case Insn::T::SIN:
            rf[insn.z] = Q8_24(sin(rf[insn.x].as_double()));
            break;
        case Insn::T::SIN2PI:
            rf[insn.z] = Q8_24(sin(2 * M_PI * rf[insn.x].as_double()));
            break;
        case Insn::T::COS:
            rf[insn.z] = Q8_24(cos(rf[insn.x].as_double()));
            break;
        case Insn::T::COS2PI:
            rf[insn.z] = Q8_24(cos(2 * M_PI * rf[insn.x].as_double()));
            break;
        case Insn::T::CONST:
            rf[insn.z] = consts.at(insn.x);
            break;
        }
    }

    return { rf[0], rf[1], { rf[2], rf[3], rf[4] } };
}

} // namespace benzene
