#pragma once

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <PEngine/Render/RCore/Texture.h>
#include <string>
#include <memory>
#include <vector>

namespace Picasso::Engine::Render::Core
{
    class TextureManager
    {
    public:
        virtual ~TextureManager(){};

        virtual bool LoadTextures(const std::vector<std::string> textures) = 0;
        virtual std::vector<std::unique_ptr<Texture>> GetTextures() = 0;
        virtual bool ActivateTextures(const unsigned int shaderProgram, Texture **textures, int tSize) = 0;
        virtual bool BindTextures(const unsigned int shaderProgram) = 0;
    };
}

#endif