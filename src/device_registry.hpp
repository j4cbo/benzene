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

#pragma once
#include <vector>

namespace benzene {

class DeviceHandle;
class Device;

/*
 * The DeviceRegistry scans for and tracks available devices.
 */
class DeviceRegistry {
public:
    /*
     * DeviceRegistry is a singleton - get() creates one if it hasn't been created, or returns
     * the existing one if it has.
     */
    static DeviceRegistry & get();

    /*
     * The DeviceRegistry looks for available devices in the background. This returns the
     * set of currently available devices.
     */
    std::vector<DeviceHandle> list();

    /*
     * Open a new connection to a device.
     */
    std::unique_ptr<Device> connect(const DeviceHandle & handle);

    DeviceRegistry(const DeviceRegistry &) = delete;
    DeviceRegistry & operator=(const DeviceRegistry &) = delete;

private:
    class Impl;
    const std::unique_ptr<Impl> m_impl;
    DeviceRegistry();
    ~DeviceRegistry();
};

} // namespace benzene
