#pragma once

#ifndef OPEN_GL_GRAPHICS_PIPELINE
#define OPEN_GL_GRAPHICS_PIPELINE

#include <memory>
#include <PEngine/Logger/Logger.h>
#include <PEngine/PState.h>
#include <PEngine/Render/RData.h>
#include <PEngine/Render/RCore/Drivers/DriverImplementation.h>
#include <PEngine/Render/RCore/RGraphicsPipeline.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    class OpenGLGraphicsPipeline : public RGraphicsPipeline
    {
    public:
        OpenGLGraphicsPipeline(std::shared_ptr<DriverImplementation> driver)
            : RGraphicsPipeline(driver) {}

        virtual ~OpenGLGraphicsPipeline() = default;

        bool BeginFrame(std::shared_ptr<RAPIData> apiData, _Float32 deltaTime, std::shared_ptr<PPlatformState> pState);
        bool EndFrame(std::shared_ptr<RAPIData> apiData, _Float32 deltaTime, std::shared_ptr<PPlatformState> pState);
    };
}

#endif
