#pragma once

#ifndef OPEN_GL_TEXTURE_MANAGER_H
#define OPEN_GL_TEXTURE_MANAGER_H

#include <PEngine/Render/RCore/TextureManager.h>

#include <Glew/glew.h>
#include <GL/glx.h>
#include <GL/gl.h>

#include <vector>
#include <string>

#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLTexture.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    class OpenGLTextureManager : public TextureManager
    {
    public:
        bool LoadTextures(std::vector<std::string> textures) override;
        std::vector<Texture *> GetTextures() override;
        bool ActivateTextures(unsigned int shaderProgram) override;

    private:
        std::vector<OpenGLTexture> m_Textures;

        bool _LoadTexture(const char *textureName);
        bool _SetTextureSampler(unsigned int shaderProgram, const char *samplerName, int textureUnit);
    };
}

#endif