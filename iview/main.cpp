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

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <fstream>
#include <thread>
#include "ilda.hpp"

#define FPS 30

void render(std::istream & fs) {
    glClear(GL_COLOR_BUFFER_BIT);

    auto pts = benzene::ilda_read(fs);

    if (!pts.size()) {
        // See if it works after a rewind...
        fs.clear();
        fs.seekg(0);
        pts = benzene::ilda_read(fs);
    }

    glBegin(GL_LINE_STRIP);

    for (const auto & pt : pts) {
        glColor3f(pt.color.r.as_double(), pt.color.g.as_double(), pt.color.b.as_double());
        glVertex2f(pt.x.as_double(), pt.y.as_double());
    }

    glEnd();
}

void usage(const char * argv0) {
    std::cerr << "Usage: " << argv0 << " file.ild\n";
    exit(1);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        usage(argv[0]);
    }

    std::ifstream f(argv[1], std::ios::binary);
    if (!f) {
        usage(argv[0]);
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        exit(1);
    }

    const int width = 600;

    SDL_Window * win = SDL_CreateWindow("iview",
                                        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                        width, width,
                                        SDL_WINDOW_OPENGL);

    SDL_GL_CreateContext(win);

    glEnable(GL_TEXTURE_2D);
    glViewport(0, 0, width, width);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, width, width, 0.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(width / 2, width / 2, 0);
    glScalef(width / 2, width / -2, 0);

    auto t = std::chrono::steady_clock::now();

    while (!SDL_QuitRequested()) {
        /* Handle SDL events */
        SDL_Event event;
        while (SDL_PollEvent(&event)) { }

        render(f);

        SDL_GL_SwapWindow(win);

        t += std::chrono::steady_clock::duration(std::chrono::seconds(1)) / FPS;
        std::this_thread::sleep_until(t);
    }

    return 0;
}
