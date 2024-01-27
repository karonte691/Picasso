#pragma once

#ifndef OPEN_GL_DRIVER_DATA_H
#define OPEN_GL_DRIVER_DATA_H

#include <bits/stdc++.h>
#include <Glew/glew.h>
#include <GL/glx.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    struct DriverContext
    {
        u_int32_t frameBufferWidth = 0;
        u_int32_t frameBufferHeight = 0;
        GLXContext glxContext = 0;
    };
}

#endif