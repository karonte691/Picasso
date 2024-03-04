#pragma once

#ifndef OPEN_GL_MATERIAL_BUILDER_H
#define OPEN_GL_MATERIAL_BUILDER_H

#include <PEngine/Render/RCore/Pipeline/PipelineDataBuilderBase.h>

#include <PEngine/File/PFLoader.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLMaterialManager.h>

#include <memory>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    class OpenGLMaterialBuilder : public Pipeline::PipelineDataBuilderBase
    {
    public:
        OpenGLMaterialBuilder();

        bool Build(Pipeline::PipelineData *pipelineData) override;

    private:
        std::unique_ptr<Drivers::OpenGL::OpenGLMaterialManager> p_MaterialManager;
    };
}

#endif // OPEN_GL_MATERIAL_BUILDER_H