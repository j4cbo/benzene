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

#include "gtest/gtest.h"
#include "segment.hpp"
#include "segment_builders.hpp"

TEST(SegmentTest, Circle) {
    const auto seg = benzene::make_circle_segment(0, 0, 0.5, { 1, 1, 1 });

    using benzene::Point;
    EXPECT_EQ(seg.eval(0, 0), Point(0, 0.5, { 1, 1, 1 }));
    EXPECT_EQ(seg.eval(0.25, 0), Point(0.5, 0, { 1, 1, 1 }));
    EXPECT_EQ(seg.eval(0.5, 0), Point(0, -0.5, { 1, 1, 1 }));
    EXPECT_EQ(seg.eval(0.75, 0), Point(-0.5, 0, { 1, 1, 1 }));
}
