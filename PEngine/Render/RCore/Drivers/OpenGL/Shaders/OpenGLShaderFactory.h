#pragma once

#ifndef OPEN_GL_SHADER_FACTORY_H
#define OPEN_GL_SHADER_FACTORY_H

#include <PEngine/Logger/Logger.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/Shaders/OpenGLShader.h>

#include <Glew/glew.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <memory>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL::Shaders
{
    struct ShaderModule
    {
        GLuint Id;
        bool Compiled = false;
    };

    class OpenGLShaderFactory
    {
    public:
        std::unique_ptr<OpenGLShader> Create(std::string vertexContent, std::string fragmentContent);

    private:
        ShaderModule _createShaderModule(std::string shaderContent, GLuint shaderType);
    };
}

#endif