#pragma once

#ifndef OPEN_GL_TEXTURE_H
#define OPEN_GL_TEXTURE_H

#include <PEngine/Render/RCore/Texture.h>

#include <Glew/glew.h>
#include <GL/glx.h>
#include <GL/gl.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    class OpenGLTexture : public Texture
    {
    public:
        bool LoadTexture(const char *textureName) override;
        bool ActivateTexture() override;

    private:
        GLuint m_TextureMemId;
    };
}

#endif