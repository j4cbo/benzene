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

#include "ilda_output_device.hpp"
#include "point.hpp"
#include <memory>
#include <fstream>

namespace benzene {

class IldaOutputDevice::Impl {
public:
    std::ofstream f;

    explicit Impl(const std::string & filename)
        : f(filename.c_str(), std::ios::out | std::ios::binary | std::ios::ate) {}
};

IldaOutputDevice::IldaOutputDevice(const std::string & filename)
    : m_impl(std::make_unique<IldaOutputDevice::Impl>(filename)) {
}

void IldaOutputDevice::write_points(const Point * points, size_t n, int /*pps*/) {

    // Write header
    const char header[] = {
        'I', 'L', 'D', 'A', 0, 0, 0, 5,         // ILDA frame header
        'f', 'r', 'a', 'm', 'e', 0, 0, 0,       // ILDA frame name
        'b', 'e', 'n', 'z', 'e', 'n', 'e', 0,   // ILDA company name
        char(n >> 8), char(n),                  // Number of points
        0, 0,                                   // Frame number (bogus)
        0, 0,                                   // Frame count (bogus)
        0,                                      // Scanner number
        0,                                      // "Future"
    };

    static_assert(sizeof(header) == 32, "header should be 32 bytes");

    m_impl->f.write(header, sizeof header);

    for (size_t i = 0; i < n; i++) {
        int16_t x = points[i].x.saturate_normal().as_q0_15();
        int16_t y = points[i].y.saturate_normal().as_q0_15();
        uint8_t r = points[i].color.r.saturate_positive_normal().as_q8();
        uint8_t g = points[i].color.g.saturate_positive_normal().as_q8();
        uint8_t b = points[i].color.b.saturate_positive_normal().as_q8();

        const char buffer[] = {
            char(x >> 8), char(x),
            char(y >> 8), char(y),
            0,
            char(b),
            char(g),
            char(r),
        };

        static_assert(sizeof(buffer) == 8, "point should be 8 bytes");

        m_impl->f.write(buffer, sizeof buffer);
    }
}

IldaOutputDevice::Status IldaOutputDevice::get_status() const {
    // An IldaOutputDevice is always logically "streaming"
    return Status::STREAMING;
}

size_t IldaOutputDevice::get_capacity() const {
    // An IldaOutputDevice always has lots of capacity.
    return 5000;
}

void IldaOutputDevice::stop() {
    // no-op
}

IldaOutputDevice::~IldaOutputDevice() = default;

/*static*/ DeviceHandle IldaOutputDevice::handle(const std::string & name) {
    return DeviceHandle([name] {
        return std::make_unique<IldaOutputDevice>(name);
    });
}

} // namespace benzene
