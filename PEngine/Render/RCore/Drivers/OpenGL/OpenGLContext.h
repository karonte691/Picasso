#pragma once

#ifndef OPEN_GL_CONTEXT_H
#define OPEN_GL_CONTEXT_H

#include <memory>
#include <GL/glx.h>
#include <PEngine/Logger/Logger.h>
#include <PEngine/PState.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    static int visualAttribs[] =
        {
            GLX_X_RENDERABLE, True,
            GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
            GLX_RENDER_TYPE, GLX_RGBA_BIT,
            GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
            GLX_RED_SIZE, 8,
            GLX_GREEN_SIZE, 8,
            GLX_BLUE_SIZE, 8,
            GLX_ALPHA_SIZE, 8,
            GLX_DEPTH_SIZE, 24,
            GLX_STENCIL_SIZE, 8,
            GLX_DOUBLEBUFFER, True,
            None};

    class OpenGLContext
    {
    public:
        GLXContext Get(std::shared_ptr<PPlatformState> pState);
        GLXFBConfig *GetFrameBufferConfig();
        bool SetCurrentContext(std::shared_ptr<PPlatformState> pState, GLXContext context, GLXWindow window);
        void ClearFrameBufferConfig();
        void DestroyContext(std::shared_ptr<PPlatformState> pState, GLXContext context);

    private:
        GLXFBConfig *p_FbConfigs;
    };
}

#endif