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

#include "ilda.hpp"

namespace benzene {

/*
 * ILDA 64-color palette
 */
static const uint8_t ilda_palette_64[] = {
    255,   0,   0, 255,  16,   0, 255,  32,   0, 255,  48,   0,
    255,  64,   0, 255,  80,   0, 255,  96,   0, 255, 112,   0,
    255, 128,   0, 255, 144,   0, 255, 160,   0, 255, 176,   0,
    255, 192,   0, 255, 208,   0, 255, 224,   0, 255, 240,   0,
    255, 255,   0, 224, 255,   0, 192, 255,   0, 160, 255,   0,
    128, 255,   0,  96, 255,   0,  64, 255,   0,  32, 255,   0,
      0, 255,   0,   0, 255,  32,   0, 255,  64,   0, 255,  96,
      0, 255, 128,   0, 255, 160,   0, 255, 192,   0, 255, 224,
      0, 130, 255,   0, 114, 255,   0, 104, 255,  10,  96, 255,
      0,  82, 255,   0,  74, 255,   0,  64, 255,   0,  32, 255,
      0,   0, 255,  32,   0, 255,  64,   0, 255,  96,   0, 255,
    128,   0, 255, 160,   0, 255, 192,   0, 255, 224,   0, 255,
    255,   0, 255, 255,  32, 255, 255,  64, 255, 255,  96, 255,
    255, 128, 255, 255, 160, 255, 255, 192, 255, 255, 224, 255,
    255, 255, 255, 255, 224, 224, 255, 192, 192, 255, 160, 160,
    255, 128, 128, 255,  96,  96, 255,  64,  64, 255,  32,  32
};

/*
 * Read a paletted color.
 */
Color color_from_palette(uint8_t b0, uint8_t b1) {
    uint16_t color = b0 << 8 | b1;
    if (color >= 64) {
        // "Blanking" flag, or bad color
        return { 0, 0, 0 };
    } else {
        return {
            ilda_palette_64[3 * color] / 255.0,
            ilda_palette_64[3 * color + 1] / 255.0,
            ilda_palette_64[3 * color + 2] / 255.0,
        };
    }
}

/*
 * Read a truecolor color.
 */
Color color_from_tc(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3) {
    if (b0 & 0x40) {
        return { 0, 0, 0 };
    } else {
        return { b3 / 255.0, b2 / 255.0, b1 / 255.0 };
    }
}

/*
 * Load an ILDA frame from a stream.
 */
std::vector<Point> ilda_read(std::istream & stream) {
    char buf[8];

    // Start by reading the ILDA header
    stream.read(buf, sizeof buf);
    if (!stream) {
        return {};
    }

    int format = buf[7];
    if (format != 0 && format != 1 && format != 4 && format != 5) {
        return {};
    }

    // Throw away "frame name" and "company name"
    stream.read(buf, sizeof buf);
    if (!stream) {
        return {};
    }
    stream.read(buf, sizeof buf);
    if (!stream) {
        return {};
    }

    // Read the rest of the header
    stream.read(buf, sizeof buf);
    if (!stream) {
        return {};
    }

    // The rest of the header contains total points, frame number, total frames,
    // scanner head, and "future". We only care about the first.
    size_t npoints = uint8_t(buf[0]) << 8 | uint8_t(buf[1]);

    std::vector<Point> out;
    out.reserve(npoints);

    const size_t bytes_per_point = (format == 0) ? 8
                                 : (format == 1) ? 6
                                 : (format == 4) ? 10
                                                 : 8;

    for (size_t i = 0; i < npoints; i++) {
        char ptbuf[10];

        stream.read(ptbuf, bytes_per_point);
        if (!stream) {
            return {};
        }

        out.emplace_back(
            Q8_24::from_q0_15(uint8_t(ptbuf[0]) << 8 | uint8_t(ptbuf[1])),
            Q8_24::from_q0_15(uint8_t(ptbuf[2]) << 8 | uint8_t(ptbuf[3])),
              (format == 0) ? color_from_palette(ptbuf[6], ptbuf[7])
            : (format == 1) ? color_from_palette(ptbuf[4], ptbuf[5])
            : (format == 4) ? color_from_tc(ptbuf[6], ptbuf[7], ptbuf[8], ptbuf[9])
                            : color_from_tc(ptbuf[4], ptbuf[5], ptbuf[6], ptbuf[7])
        );
    }

    return out;
}

} // namespace benzene
