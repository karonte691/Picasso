#pragma once

#ifndef OPEN_GL_DRIVER_H
#define OPEN_GL_DRIVER_H

#include <PEngine/Logger/Logger.h>
#include <PEngine/Render/RData.h>
#include <PEngine/Render/RCore/Drivers/DriverImplementation.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLData.h>

namespace Picasso::Engine::Render::Core::Drivers
{
    using Picasso::Engine::Render::Core::Drivers::OpenGL::DriverContext;

    class OpenGLDriver : public DriverImplementation
    {
    public:
        bool InitDriver(std::shared_ptr<RAPIData> rcData, const char *appName, std::shared_ptr<PPlatformState> pState, EngineState *eState) override;
        void OnResize(u_int16_t width, u_int16_t height) override;
        bool BeginFrame(std::shared_ptr<RAPIData> apiData, _Float32 deltaTime, std::shared_ptr<PPlatformState> pState) override;
        bool EndFrame(std::shared_ptr<RAPIData> apiData, _Float32 deltaTime) override;
        void Shutdown() override;

    private:
        DriverContext *p_Context;
        std::shared_ptr<PPlatformState> p_PlatformState;

        bool _InitOpenGl();
    };
}

#endif