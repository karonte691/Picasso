#pragma once

#ifndef OPEN_GL_MESH_BUILDER_H
#define OPEN_GL_MESH_BUILDER_H

#include <PEngine/Render/RCore/Pipeline/PipelineDataBuilderBase.h>

#include <PEngine/File/PFLoader.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLMeshManager.h>
#include <PEngine/Render/RCore/Primitives/Quad.h>

#include <memory>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    class OpenGLMeshBuilder : public Pipeline::PipelineDataBuilderBase
    {
    public:
        OpenGLMeshBuilder();

        bool Build(Pipeline::PipelineData *pipelineData) override;

    private:
        std::unique_ptr<OpenGLMeshManager> p_MeshManager;
    };
}

#endif // OPEN_GL_MESH_BUILDER_H