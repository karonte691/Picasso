#pragma once

#ifndef OPEN_GL_TEXTURE_MANAGER_H
#define OPEN_GL_TEXTURE_MANAGER_H

#include <PEngine/Render/RCore/TextureManager.h>

#include <Glew/glew.h>
#include <GL/glx.h>
#include <GL/gl.h>

#include <vector>
#include <string>
#include <memory>

#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLTexture.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    class OpenGLTextureManager : public TextureManager
    {
    public:
        bool LoadTextures(const std::vector<std::string> textures) override;
        std::vector<std::unique_ptr<Texture>> GetTextures() override;
        bool ActivateTextures(const unsigned int shaderProgram) override;
        bool BindTextures(const unsigned int shaderProgram) override;

    private:
        std::vector<OpenGLTexture> m_Textures;

        bool _LoadTexture(const char *textureName, const unsigned int textureUnit);
    };
}

#endif