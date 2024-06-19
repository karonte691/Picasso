#pragma once

#ifndef OPEN_GL_GRAPHICS_RENDER_H
#define OPEN_GL_GRAPHICS_RENDER_H

#include <PEngine/Render/RCore/Pipeline/PipelineDataBuilderBase.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLVPMatrixManager.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLTextureManager.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLLightManager.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLMaterialManager.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLMesh.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLMeshManager.h>

#include <memory>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    class OpenGLGraphicsRender
    {
    public:
        OpenGLGraphicsRender() : p_TextureManager(std::make_unique<OpenGLTextureManager>()),
                                 p_VPMatrixManager(std::make_unique<OpenGLVPMatrixManager>()),
                                 p_LightManager(std::make_unique<OpenGLLightManager>()),
                                 p_MaterialManager(std::make_unique<OpenGLMaterialManager>()),
                                 p_MeshManager(std::make_unique<OpenGLMeshManager>()) {}
        void SetUp(float width, float height);
        void ResizeFrame(float width, float height);
        void Uniforms(const Pipeline::PipelineData *pipelineData);
        bool BeginRenderFrame(const Pipeline::PipelineData *pipelineData);
        void EndRenderFrame(const Pipeline::PipelineData *pipelineData);
        void UpdateView(const Pipeline::PipelineData *pipelineData);
        void UpdateCameraPosition(const Pipeline::PipelineData *pipelineData);
        void UpdateMeshesModelMatrix(const Pipeline::PipelineData *pipelineData,
                                     float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz);

    private:
        std::unique_ptr<OpenGLTextureManager> p_TextureManager;
        std::unique_ptr<OpenGLVPMatrixManager> p_VPMatrixManager;
        std::unique_ptr<OpenGLLightManager> p_LightManager;
        std::unique_ptr<OpenGLMaterialManager> p_MaterialManager;
        std::unique_ptr<OpenGLMeshManager> p_MeshManager;
    };
}

#endif // OPEN_GL_GRAPHICS_RENDER_H