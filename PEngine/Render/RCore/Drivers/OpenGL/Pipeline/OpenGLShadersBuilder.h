#pragma once

#ifndef OPEN_GL_SHADERS_BUILDER_H
#define OPEN_GL_SHADERS_BUILDER_H

#include <PEngine/Render/RCore/Pipeline/PipelineDataBuilderBase.h>

#include <PEngine/File/PFLoader.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/Shaders/OpenGLShaderFactory.h>

#include <memory>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    class OpenGLShadersBuilder : public Pipeline::PipelineDataBuilderBase
    {
    public:
        OpenGLShadersBuilder();

        bool Build(Pipeline::PipelineData *pipelineData) override;

    private:
        std::unique_ptr<Picasso::Engine::File::PFLoader> p_FileLoader;
        std::unique_ptr<Picasso::Engine::Render::Core::Drivers::OpenGL::Shaders::OpenGLShaderFactory> p_ShaderFactory;
    };
}

#endif // OPEN_GL_SHADERS_BUILDER_H
