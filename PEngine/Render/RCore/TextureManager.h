#pragma once

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <string>
#include <vector>

#include <PEngine/Render/RCore/Texture.h>

namespace Picasso::Engine::Render::Core
{
    class TextureManager
    {
    public:
        virtual ~TextureManager(){};

        virtual bool LoadTextures(std::vector<std::string> textures) = 0;
        virtual std::vector<Texture *> GetTextures() = 0;
        virtual bool ActivateTextures(unsigned int shaderProgram) = 0;
    };
}

#endif