#pragma once

#ifndef OPEN_GL_SHADER_H
#define OPEN_GL_SHADER_H

#include <PEngine/Logger/Logger.h>
#include <PEngine/Render/RCore/RShader.h>

#include <Glew/glew.h>
#include <GL/gl.h>
#include <GL/glx.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL::Shaders
{
    class OpenGLShader : public RShader
    {
    public:
        OpenGLShader(GLuint id);

        GLuint GetId() { return m_Id; };

        void Use() override;
        void Destroy() override;

    private:
        GLuint m_Id;
    };
}

#endif