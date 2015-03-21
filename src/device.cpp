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

#include "device.hpp"
#include "segment.hpp"
#include "segment_builders.hpp"
#include "output_device.hpp"

namespace benzene {

void Device::draw_rect(double x1, double y1, double x2, double y2, const Color & color) {
    draw_line(x1, y1, x2, y1, color);
    draw_line(x2, y1, x2, y2, color);
    draw_line(x2, y2, x1, y2, color);
    draw_line(x1, y2, x1, y1, color);
}

void Device::draw_line(double x1, double y1, double x2, double y2, const Color & color) {
    m_segment_buffer.push_back(make_line_segment(x1, y1, x2, y2, color));
}

void Device::draw_circle(double x, double y, double r, const Color & color) {
    m_segment_buffer.push_back(make_circle_segment(x, y, r, color));
}

void Device::flip() {
    // TODO
}

void Device::wait_for_ready() {
    // TODO
}

Device::Device(std::unique_ptr<OutputDevice> output) : m_output_device(std::move(output)) {
    // TODO
}

Device::~Device() = default;

} // namespace benzene
