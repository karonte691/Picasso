#include <PEngine/Render/RCore/Drivers/OpenGL/Pipeline/OpenGLTextureBuilder.h>

#include <PEngine/Logger/Logger.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    OpenGLTextureBuilder::OpenGLTextureBuilder()
    {
        p_TextureManager = std::make_unique<Drivers::OpenGL::OpenGLTextureManager>();
    }

    /**
     * @brief Builds the OpenGL texture for the pipeline.
     *
     * This function loads the required textures and sets them in the pipeline data.
     *
     * @param pipelineData A pointer to the pipeline data.
     * @return True if the texture build was successful, false otherwise.
     */
    bool OpenGLTextureBuilder::Build(Pipeline::PipelineData *pipelineData)
    {
        std::vector<std::string> texturesToLoad;

        texturesToLoad.push_back("zelda.png");

        if (!p_TextureManager->LoadTextures(texturesToLoad))
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLTextureBuilder] Unable to load the texture");
            return false;
        }

        pipelineData->textures = p_TextureManager->GetTextures();

        return true;
    }
}