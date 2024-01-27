#pragma once

#ifndef DRIVER_IMPLEMENTATION_H
#define DRIVER_IMPLEMENTATION_H

#include <memory>
#include <PEngine/PState.h>
#include <PEngine/Render/RData.h>

namespace Picasso::Engine::Render::Core::Drivers
{
    enum RDRIVERS
    {
        VULKAN,
        OPEN_GL
        // DIRECTX NOT SUPPORTED
    };

    class DriverImplementation
    {
    public:
        virtual ~DriverImplementation() {}

        virtual bool InitDriver(std::shared_ptr<RAPIData> rcData, const char *appName, std::shared_ptr<PPlatformState> pState, EngineState *eState) = 0;
        virtual void OnResize(u_int16_t width, u_int16_t height) = 0;
        virtual bool BeginFrame(std::shared_ptr<RAPIData> apiData, _Float32 deltaTime, std::shared_ptr<PPlatformState> pState) = 0;
        virtual bool EndFrame(std::shared_ptr<RAPIData> apiData, _Float32 deltaTime, std::shared_ptr<PPlatformState> pState) = 0;
        virtual void Shutdown() = 0;
        virtual RDRIVERS GetType() = 0;
    };
}

#endif