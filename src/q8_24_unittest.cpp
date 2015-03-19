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
#include "gtest/gtest.h"

using namespace benzene;

TEST(Q8_24Test, BasicArithmetic) {
    EXPECT_EQ(Q8_24(10) + Q8_24(0.125), Q8_24(10.125));
    EXPECT_EQ(Q8_24(10.75) - Q8_24(4.25), Q8_24(6.5));
    EXPECT_EQ(Q8_24(7.5) % Q8_24(2.0), Q8_24(1.5));
    EXPECT_EQ(Q8_24(2.5) * Q8_24(2.5), Q8_24(6.25));
    EXPECT_EQ(Q8_24(6.1875) / Q8_24(1.375), Q8_24(4.5));
}

TEST(Q8_24Test, Negative) {
    EXPECT_EQ(Q8_24(-1.0) + Q8_24(-0.5), Q8_24(-1.5));
    EXPECT_EQ(Q8_24(-1.0) * Q8_24(0.5), Q8_24(-0.5));
    EXPECT_EQ(Q8_24(-2.0) * Q8_24(-1.5), Q8_24(3.0));
    EXPECT_EQ(Q8_24(-1.0) / Q8_24(0.5), Q8_24(-2.0));
    EXPECT_EQ(Q8_24(-0.5) / Q8_24(4.0), Q8_24(-0.125));
    EXPECT_EQ(Q8_24(-2.0) / Q8_24(-4.0), Q8_24(0.5));
}
