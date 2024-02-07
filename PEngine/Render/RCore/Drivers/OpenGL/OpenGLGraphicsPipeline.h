#pragma once

#ifndef OPEN_GL_GRAPHICS_PIPELINE_H
#define OPEN_GL_GRAPHICS_PIPELINE_H

#include <memory>
#include <PEngine/Logger/Logger.h>
#include <PEngine/PState.h>
#include <PEngine/Render/RData.h>
#include <PEngine/File/PFLoader.h>
#include <PEngine/Render/RCore/Drivers/DriverImplementation.h>
#include <PEngine/Render/RCore/RGraphicsPipeline.h>
#include <PEngine/Render/RCore/Vertex.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/Shaders/OpenGLShaderFactory.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLTexture.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    class OpenGLGraphicsPipeline : public RGraphicsPipeline
    {
    public:
        OpenGLGraphicsPipeline(DriverImplementation *driver)
            : RGraphicsPipeline(driver) {}

        bool Init() override;
        bool BeginFrame(RAPIData *apiData, float deltaTime, PPlatformState *pState) override;
        bool EndFrame(RAPIData *apiData, float deltaTime, PPlatformState *pState) override;

    private:
        std::unique_ptr<Picasso::Engine::File::PFLoader> p_FileLoader;
        std::unique_ptr<Shaders::OpenGLShaderFactory> p_ShaderFactory;
        std::unique_ptr<Shaders::OpenGLShader> p_Shader;
        std::unique_ptr<OpenGLTexture> p_Texture;
        Vertex m_Vertices[3];
        GLuint m_Indices[3];
        GLuint m_VAD;
        GLuint m_VB0;
        GLuint m_EBO;
    };
}

#endif
