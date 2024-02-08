#pragma once

#ifndef OPEN_GL_TEXTURE_H
#define OPEN_GL_TEXTURE_H

#include <Glew/glew.h>
#include <GL/glx.h>
#include <GL/gl.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    class OpenGLTexture
    {
    public:
        GLuint Id;
        int Width;
        int Height;

        OpenGLTexture(GLuint id) : Id(id){};

        bool ActivateTexture(unsigned int unit);
    };
}

#endif