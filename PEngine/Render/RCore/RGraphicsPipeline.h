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
     *  Each driver has it's own implementation of the graphics pipeline. This class
     *  serve the purpose to abstract the low level code from this layer of Picasso
     */
    class RGraphicsPipeline
    {
    public:
        RGraphicsPipeline(DriverImplementation *driver) : p_Driver(driver){};
        virtual ~RGraphicsPipeline() = default;

        virtual bool Init() = 0;
        virtual bool BeginFrame(RAPIData *apiData, float deltaTime, PPlatformState *pState) = 0;
        virtual bool EndFrame(RAPIData *apiData, float deltaTime, PPlatformState *pState) = 0;

    protected:
        DriverImplementation *p_Driver;
    };
}

#endif