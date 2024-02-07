#include <PEngine/File/PFLoader.h>

namespace Picasso::Engine::File
{
    PFile PFLoader::LoadShader(std::string shaderName)
    {
        std::string shaderDir = "Data/Shader/";

        std::string fullShaderPath = shaderDir + shaderName;

        return FileManager::Instance->Read(fullShaderPath);
    }

    PFile PFLoader::LoadTexture(std::string textureName)
    {
        std::string textureDir = "Data/Texture/";

        std::string texturePathPath = textureDir + textureName;

        return FileManager::Instance->Read(texturePathPath);
    }
}