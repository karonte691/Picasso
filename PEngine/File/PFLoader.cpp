#include <PEngine/File/PFLoader.h>

namespace Picasso::Engine::File
{
    PFile PFLoader::LoadShader(std::string shaderName)
    {
        std::string shaderDir = "Data/Shader/";

        std::string fullShaderPathPath = shaderDir + shaderName;

        return FileManager::Instance->Read(fullShaderPathPath);
    }
}