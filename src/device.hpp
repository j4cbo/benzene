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
#include <memory>

#include "color.hpp"

namespace benzene {

class Segment;
class OutputDevice;

class Device {
public:
    void draw_circle(double x, double y, double r, const Color & color);
    void draw_line(double x1, double y1, double x2, double y2, const Color & color);

    /* Convenience function - equivalent to four draw_line() calls */
    void draw_rect(double x1, double y1, double x2, double y2, const Color & color);

    void flip();

    void wait_for_ready();

    ~Device();

    explicit Device(std::unique_ptr<OutputDevice>);
    Device(const Device &) = delete;

private:
    const std::unique_ptr<OutputDevice> m_output_device;
    std::vector<Segment> m_segment_buffer;
};

} // namespace benzene
