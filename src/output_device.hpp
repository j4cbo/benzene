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

#include <cstddef>

namespace benzene {

struct Point;

class OutputDevice {
public:
    /*
     * OutputDevice interface
     *
     * This abstract class is implemented by output device drivers: ILDA file, Ether Dream,
     * sound card, etc.
     */

    /*
     * Add a set of points to the output buffer. These points should be rendered at n pps.
     *
     * - If called when get_status() is ERROR, this is a no-op. (The status of a device can
     *   enter the ERROR state asynchronously.)
     * - If n is greater than get_capacity(), this will throw an exception.
     *
     * NOTE:
     * Streaming output devices have a fixed buffer and so will enforce real-time streaming.
     * An ILDA file writer may not implement flow control at all (get_capacity() will always
     * be very large).
     */
    virtual void write_points(const Point * points, size_t n, int pps) = 0;

    /*
     * Get the status of the device.
     * - ERROR: The device has entered an error state (connection broken, etc). Calling code
     *          should dispose of this OutputDevice, but may attempt to reconnect by creating
     *          a new one.
     *
     * - IDLE: The device is not currently generating output.
     *
     * - STREAMING: The device is currently generating output.
     */
    enum class Status { ERROR, IDLE, STREAMING };
    virtual Status get_status() const = 0;

    /*
     * Return how many points can be written with the next call to write_points().
     */
    virtual size_t get_capacity() const = 0;

    /*
     * Stop output immediately.
     */
    virtual void stop() = 0;

    /*
     * Destructor.
     */
    virtual ~OutputDevice() {}

    /*
     * Disallow copying and assigning
     */
    OutputDevice(const OutputDevice &) = delete;
    OutputDevice & operator=(const OutputDevice &) = delete;

protected:
    OutputDevice() {}
};

} // namespace benzene
