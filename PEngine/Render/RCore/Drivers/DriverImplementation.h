#pragma once

#ifndef DRIVER_IMPLEMENTATION_H
#define DRIVER_IMPLEMENTATION_H

#include <memory>
#include <PEngine/PState.h>
#include <PEngine/Render/RData.h>

namespace Picasso::Engine::Render::Core::Drivers
{
    class DriverImplementation
    {
    public:
        virtual ~DriverImplementation() {}

        virtual bool InitDriver(std::shared_ptr<RAPIData> rcData, const char *appName, std::shared_ptr<PPlatformState> pState, EngineState *eState) = 0;
        virtual void Shutdown() = 0;
    };
}

#endif