#pragma once

#ifndef P_F_LOADER_H
#define P_F_LOADER_H

#include <string>
#include <PEngine/File/FileManager.h>

namespace Picasso::Engine::File
{
    class PFLoader
    {
    public:
        PFile LoadShader(std::string shaderName);
        PFile LoadTexture(std::string textureName);
    };
}
#endif