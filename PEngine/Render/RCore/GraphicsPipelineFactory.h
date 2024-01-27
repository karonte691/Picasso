#pragma once

#ifndef GRAPHICS_PIPELINE_FACTORY_H
#define GRAPHICS_PIPELINE_FACTORY_H

#include <memory>
#include <PEngine/Logger/Logger.h>
#include <PEngine/PState.h>
#include <PEngine/Render/RData.h>
#include <PEngine/Render/RCore/Drivers/DriverImplementation.h>
#include <PEngine/Render/RCore/RGraphicsPipeline.h>

namespace Picasso::Engine::Render::Core
{
    class GraphicsPipelineFactory
    {
    public:
        std::shared_ptr<RGraphicsPipeline> Get(std::shared_ptr<DriverImplementation> driver);
    };
}
#endif