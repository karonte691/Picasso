#pragma once

#ifndef OPEN_GL_DRIVER_H
#define OPEN_GL_DRIVER_H

#include <PEngine/Logger/Logger.h>
#include <PEngine/Render/RData.h>
#include <PEngine/Render/RCore/Drivers/DriverImplementation.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLData.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLContext.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLWindow.h>

namespace Picasso::Engine::Render::Core::Drivers
{
    using Picasso::Engine::Render::Core::Drivers::OpenGL::OpenGLContext;
    using Picasso::Engine::Render::Core::Drivers::OpenGL::OpenGLWindow;

    class OpenGLDriver : public DriverImplementation
    {
    public:
        bool InitDriver(RAPIData *rcData, const char *appName, PPlatformState *pState, EngineState *eState) override;
        void OnResize(u_int16_t width, u_int16_t height) override;
        bool BeginFrame(RAPIData *apiData, _Float32 deltaTime, PPlatformState *pState) override;
        bool EndFrame(RAPIData *apiData, _Float32 deltaTime, PPlatformState *pState) override;
        void Shutdown() override;
        RDRIVERS GetType() override;

    private:
        Picasso::Engine::Render::Core::Drivers::OpenGL::DriverContext *p_Context;
        PPlatformState *p_PlatformState;
        OpenGLContext *p_OpenGLContext;
        OpenGLWindow *p_OpenGLWindow;

        bool _InitOpenGl();
    };
}

#endif