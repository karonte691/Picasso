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
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLVPMatrixManager.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLTextureManager.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLLightManager.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLMaterialManager.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLMesh.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLMeshManager.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/Pipeline/OpenGLPipelineDataBuilderManager.h>
#include <PEngine/EventSystem/PERegistry.h>
#include <PEngine/Math/Mat4.h>

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
        std::unique_ptr<OpenGLTextureManager> p_TextureManager;
        std::unique_ptr<OpenGLVPMatrixManager> p_VPMatrixManager;
        std::unique_ptr<OpenGLLightManager> p_LightManager;
        std::unique_ptr<OpenGLPipelineDataBuilderManager> p_PipelineDataBuilder;
        std::unique_ptr<OpenGLMaterialManager> p_MaterialManager;
        std::unique_ptr<OpenGLMeshManager> p_MeshManager;
        Pipeline::PipelineData m_PipelineData;

        void _onRenderUpdate(BaseEvent<PEvent> *&event);
    };
}

#endif
