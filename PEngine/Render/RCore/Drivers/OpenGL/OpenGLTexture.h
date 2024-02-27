#pragma once

#ifndef OPEN_GL_TEXTURE_H
#define OPEN_GL_TEXTURE_H

#include <Glew/glew.h>
#include <GL/glx.h>
#include <GL/gl.h>

#include <PEngine/Render/RCore/Texture.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    class OpenGLTexture : public Texture
    {
    public:
        OpenGLTexture(GLuint id) : Texture(id){};

        bool ActivateTexture(unsigned int unit);
    };
}

#endif