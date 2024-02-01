#pragma once

#ifndef OPEN_GL_WINDOW_H
#define OPEN_GL_WINDOW_H

#include <memory>
#include <Glew/glew.h>
#include <GL/glx.h>
#include <PEngine/Logger/Logger.h>
#include <PEngine/PState.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    class OpenGLWindow
    {
    public:
        GLXWindow Get(PPlatformState *pState, GLXFBConfig *frameBufferConfigs);
    };
}

#endif