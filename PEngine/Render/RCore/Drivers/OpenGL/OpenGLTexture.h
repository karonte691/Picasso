#pragma once

#ifndef OPEN_GL_TEXTURE_H
#define OPEN_GL_TEXTURE_H

#include <Glew/glew.h>
#include <GL/glx.h>
#include <GL/gl.h>

#include <PEngine/Render/RCore/Texture.h>

#include <string>
namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    class OpenGLTexture : public Texture
    {
    public:
        OpenGLTexture(unsigned int id, unsigned int textureUnit, unsigned int width, unsigned int height)
            : Texture(id, textureUnit, width, height){};

        bool ActivateTexture(unsigned int unit);
        bool UniformTexture(unsigned int unit, unsigned int shaderProgram, const char *samplerName);
    };
}

#endif