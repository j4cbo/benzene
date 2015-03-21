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
#include "device_handle.hpp"
#include "device_registry.hpp"
#include "output_device.hpp"

namespace benzene {

/*static*/ DeviceRegistry & DeviceRegistry::get() {
    static DeviceRegistry reg;
    return reg;
}

class DeviceRegistry::Impl {
    // TODO
};

DeviceRegistry::DeviceRegistry() : m_impl(std::make_unique<Impl>()) {}
DeviceRegistry::~DeviceRegistry() = default;

std::unique_ptr<Device> DeviceRegistry::connect(const DeviceHandle & handle) {
    return std::make_unique<Device>(handle.func());
}

} // namespace benzene
