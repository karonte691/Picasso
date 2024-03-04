#include <PEngine/Render/RCore/Drivers/OpenGL/Pipeline/OpenGLMaterialBuilder.h>

#include <PEngine/Logger/Logger.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    OpenGLMaterialBuilder::OpenGLMaterialBuilder()
    {
        p_MaterialManager = std::make_unique<Drivers::OpenGL::OpenGLMaterialManager>();
    }

    /**
     * @brief Builds materials for the OpenGL pipeline.
     *
     * This function iterates over the textures in the pipeline data and creates materials
     * using the MaterialManager. Each material is assigned a diffuse texture and a specular texture.
     * If any of the textures are null or have an ID of 0, an error message is logged and the material is skipped.
     * The created materials are then added to the pipeline data.
     *
     * @param pipelineData A pointer to the PipelineData object.
     * @return True if the materials were successfully built, false otherwise.
     */
    bool OpenGLMaterialBuilder::Build(Pipeline::PipelineData *pipelineData)
    {
        for (size_t i = 0; i < pipelineData->textures.size(); i++)
        {
            std::unique_ptr<Texture> &texture = pipelineData->textures[i];
            std::unique_ptr<Material> material = p_MaterialManager->CreateMaterial(
                Math::Vector3(0.1f, 0.1f, 0.1f),
                Math::Vector3(1.0f, 1.0f, 1.0f),
                Math::Vector3(1.0f, 1.0f, 1.0f),
                32.0f,
                texture.get(), texture.get());

            if (material->DiffuseTexture == nullptr || material->SpecularTexture == nullptr)
            {
                Picasso::Engine::Logger::Logger::Error("[OpenGLMaterialBuilder] material textures are null");
                continue;
            }

            if (material->DiffuseTexture->Id == 0 || material->SpecularTexture->Id == 0)
            {
                Picasso::Engine::Logger::Logger::Error("[OpenGLMaterialBuilder] material textures are null");
                continue;
            }

            pipelineData->materials.push_back(std::move(material));
        }

        return true;
    }
}