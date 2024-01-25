#pragma once

#ifndef OPEN_GL_SHADER_H
#define OPEN_GL_SHADER_H

#include <PEngine/Logger/Logger.h>

#include <Glew/glew.h>
#include <GL/gl.h>
#include <GL/glx.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL::Shaders
{
    class OpenGLShader
    {
    public:
        OpenGLShader(GLuint id);
        void Use();
        void Destroy();

    private:
        GLuint m_Id;
    };
}

#endif