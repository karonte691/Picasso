#pragma once

#ifndef R_GRAPHICS_PIPELINE_H
#define R_GRAPHICS_PIPELINE_H

#include <memory>
#include <PEngine/Logger/Logger.h>
#include <PEngine/PState.h>
#include <PEngine/Render/RData.h>
#include <PEngine/Render/RCore/Drivers/DriverImplementation.h>

namespace Picasso::Engine::Render::Core
{
    using Picasso::Engine::Render::RAPIData;
    using Picasso::Engine::Render::Core::Drivers::DriverImplementation;

    /**
     *  Each driver has it's own children implementation of the graphics pipeline. This class
     *  serve the purpose to abstract the low level code from this layer of Picasso
     */
    class RGraphicsPipeline
    {
    public:
        RGraphicsPipeline(std::shared_ptr<DriverImplementation> driver) : p_Driver(driver){};

        virtual bool BeginFrame(std::shared_ptr<RAPIData> apiData, _Float32 deltaTime, std::shared_ptr<PPlatformState> pState) = 0;
        virtual bool EndFrame(std::shared_ptr<RAPIData> apiData, _Float32 deltaTime, std::shared_ptr<PPlatformState> pState) = 0;

    protected:
        std::shared_ptr<DriverImplementation> p_Driver;
    };
}

#endif