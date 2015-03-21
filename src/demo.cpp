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

#include "device_registry.hpp"
#include "device_handle.hpp"
#include "device.hpp"
#include "ilda_output_device.hpp"

/*
 * Let's draw a square.
 */
void test() {

    auto & r = benzene::DeviceRegistry::get();
    auto dev = r.connect(benzene::IldaOutputDevice::handle("demo.ild"));

    dev->draw_circle(0, 0, 0.5, { 1, 1, 1 });
    dev->draw_rect(-0.75, -0.75, 0.75, 0.75, { 1, 1, 1 });
    dev->flip();
    dev->wait_for_ready();
}
