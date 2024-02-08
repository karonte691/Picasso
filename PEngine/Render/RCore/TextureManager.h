#pragma once

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <string>
#include <vector>

namespace Picasso::Engine::Render::Core
{
    class TextureManager
    {
    public:
        virtual ~TextureManager(){};

        virtual bool LoadTextures(std::vector<std::string> textures) = 0;
        virtual bool ActivateTextures(unsigned int shaderProgram) = 0;
    };
}

#endif