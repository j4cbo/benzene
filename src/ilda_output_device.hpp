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

#include "output_device.hpp"
#include <memory>

namespace benzene {

class IldaOutputDevice : public OutputDevice {
public:
    /*
     * OutputDevice that writes to an ILDA file
     */
    IldaOutputDevice(const std::string & filename);

    virtual void write_points(const Point * points, size_t n, int pps) override;
    virtual Status get_status() const override;
    virtual size_t get_capacity() const override;
    virtual void stop() override;
    virtual ~IldaOutputDevice() override;

private:
    class Impl;
    const std::unique_ptr<Impl> m_impl;
};

} // namespace benzene
