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

#include "segment.hpp"

namespace benzene {

/*
 * Create a Segment that will draw a straight line from (x1, y1) to (x2, y2)
 */
Segment make_line_segment(double x1, double y1, double x2, double y2, const Color & color);

/*
 * Create a Segment that will draw a circle around (x1, y1) at radius r
 */
Segment make_circle_segment(double x1, double y1, double r, const Color & color);

} // namespace benzene
