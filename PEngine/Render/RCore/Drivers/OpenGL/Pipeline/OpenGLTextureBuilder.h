#pragma once

#ifndef OPEN_GL_TEXTURE_BUILDER_H
#define OPEN_GL_TEXTURE_BUILDER_H

#include <PEngine/Render/RCore/Pipeline/PipelineDataBuilderBase.h>

#include <PEngine/File/PFLoader.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLTextureManager.h>

#include <memory>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    class OpenGLTextureBuilder : public Pipeline::PipelineDataBuilderBase
    {
    public:
        OpenGLTextureBuilder();

        bool Build(Pipeline::PipelineData *pipelineData) override;

    private:
        std::unique_ptr<Drivers::OpenGL::OpenGLTextureManager> p_TextureManager;
    };
}

#endif // OPEN_GL_TEXTURE_BUILDER_H