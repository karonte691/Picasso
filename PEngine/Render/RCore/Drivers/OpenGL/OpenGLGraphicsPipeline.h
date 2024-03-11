#pragma once

#ifndef OPEN_GL_GRAPHICS_PIPELINE_H
#define OPEN_GL_GRAPHICS_PIPELINE_H

#include <memory>
#include <PEngine/Logger/Logger.h>
#include <PEngine/PState.h>
#include <PEngine/Render/RData.h>
#include <PEngine/File/PFLoader.h>
#include <PEngine/Render/RCore/RGraphicsPipeline.h>
#include <PEngine/Render/RCore/Vertex.h>
#include <PEngine/Render/RCore/Material.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/Pipeline/OpenGLPipelineDataBuilderManager.h>
#include <PEngine/EventSystem/PERegistry.h>
#include <PEngine/Math/Mat4.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLGraphicsRender.h>
namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    using Picasso::Engine::EventSystem::PicassoRegistry;
    using Picasso::Engine::EventSystem::Events::BaseEvent;
    using Picasso::Engine::EventSystem::Events::PEvent;

    class OpenGLGraphicsPipeline : public RGraphicsPipeline
    {
    public:
        OpenGLGraphicsPipeline(DriverImplementation *driver)
            : RGraphicsPipeline(driver) {}

        bool Init(RAPIData *apiData) override;
        void Shutdown() override;
        void RegisterHooks() override;
        bool BeginFrame(RAPIData *apiData, float deltaTime, PPlatformState *pState) override;
        bool EndFrame(RAPIData *apiData, float deltaTime, PPlatformState *pState) override;
        bool Resize(u_int16_t width, u_int16_t height) override;

    private:
        std::unique_ptr<OpenGLPipelineDataBuilderManager> p_PipelineDataBuilder;
        std::unique_ptr<OpenGLGraphicsRender> p_GraphicsRender;
        Pipeline::PipelineData m_PipelineData;

        void _OnRenderUpdateMovement(BaseEvent<PEvent> *&event);
        void _OnRenderUpdateCameraView(BaseEvent<PEvent> *&event);
        void _OnRenderUpdateCameraPosition(BaseEvent<PEvent> *&event);
    };
}

#endif // OPEN_GL_GRAPHICS_PIPELINE_H