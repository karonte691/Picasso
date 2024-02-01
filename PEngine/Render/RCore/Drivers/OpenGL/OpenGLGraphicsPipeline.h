#pragma once

#ifndef OPEN_GL_GRAPHICS_PIPELINE
#define OPEN_GL_GRAPHICS_PIPELINE

#include <memory>
#include <PEngine/Logger/Logger.h>
#include <PEngine/PState.h>
#include <PEngine/Render/RData.h>
#include <PEngine/File/PFLoader.h>
#include <PEngine/Render/RCore/Drivers/DriverImplementation.h>
#include <PEngine/Render/RCore/RGraphicsPipeline.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/Shaders/OpenGLShaderFactory.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    class OpenGLGraphicsPipeline : public RGraphicsPipeline
    {
    public:
        OpenGLGraphicsPipeline(DriverImplementation *driver)
            : RGraphicsPipeline(driver) {}

        ~OpenGLGraphicsPipeline();

        bool BeginFrame(RAPIData *apiData, _Float32 deltaTime, PPlatformState *pState) override;
        bool EndFrame(RAPIData *apiData, _Float32 deltaTime, PPlatformState *pState) override;

    private:
        Picasso::Engine::File::PFLoader *p_FileLoader;
        Shaders::OpenGLShaderFactory *p_ShaderFactory;
        bool m_PipelineStarted;

        bool _initPipeline();
    };
}

#endif
