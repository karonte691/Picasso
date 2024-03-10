#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLGraphicsRender.h>
#include <PEngine/Logger/Logger.h>
#include <PEngine/EventSystem/DeferredEventsStore.h>
#include <PEngine/EventSystem/Events/EventTypes.h>

#include <vector>
#include <map>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    /**
     * @brief Sets up the OpenGL graphics render.
     *
     * @param width The width of the viewport.
     * @param height The height of the viewport.
     */
    void OpenGLGraphicsRender::SetUp(float width, float height)
    {
        p_VPMatrixManager->CreateProjectionMatrix(width, height);

        // lights
        p_LightManager->SetLightPosition(Math::Vector3(0.0f, 0.0f, 1.0f));
    }

    /**
     * @brief Resets the OpenGL graphics render.
     *
     * @param width The width of the viewport.
     * @param height The height of the viewport.
     */
    void OpenGLGraphicsRender::ResizeFrame(float width, float height)
    {
        p_VPMatrixManager->CreateProjectionMatrix(width, height);
    }

    /**
     * @brief Sets the uniforms for the OpenGL graphics render.
     *
     * @param pipelineData The pipeline data containing the shader and other data.
     */
    void OpenGLGraphicsRender::Uniforms(const Pipeline::PipelineData *pipelineData)
    {
        p_VPMatrixManager->UniformViewMatrix(pipelineData->shader->GetId());
        p_VPMatrixManager->UniforProjectionMatrix(pipelineData->shader->GetId());
        p_LightManager->UniformLightPosition(pipelineData->shader->GetId());
    }

    /**
     * @brief Begins the rendering process for the OpenGL graphics render.
     *
     * @param pipelineData The pipeline data containing the shader, textures, materials, and meshes.
     * @return True if the rendering process is successful, false otherwise.
     */
    bool OpenGLGraphicsRender::BeginRenderFrame(const Pipeline::PipelineData *pipelineData)
    {
        pipelineData->shader->Use();

        int textureCount = pipelineData->textures.size();
        int materialCount = pipelineData->materials.size();
        Texture **textures = new Texture *[textureCount];
        Material **materials = new Material *[materialCount];

        for (int i = 0; i < textureCount; ++i)
        {
            textures[i] = pipelineData->textures[i].get();
        }
        for (int i = 0; i < materialCount; ++i)
        {
            materials[i] = pipelineData->materials[i].get();
        }

        _UpdateData(pipelineData);

        p_VPMatrixManager->UniformViewMatrix(pipelineData->shader->GetId());
        p_VPMatrixManager->UniforProjectionMatrix(pipelineData->shader->GetId());

        if (!p_TextureManager->ActivateTextures(pipelineData->shader->GetId(), textures, textureCount))
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLGraphicsPipeline] unable to activate textures");

            delete[] textures;
            delete[] materials;
            return false;
        }

        for (unsigned int i = 0; i < pipelineData->materials.size(); ++i)
        {
            p_MaterialManager->SendMaterialToShader(pipelineData->materials[i].get(), pipelineData->shader.get());
        }

        for (unsigned int i = 0; i < pipelineData->meshes.size(); ++i)
        {
            OpenGLMesh *openGLMesh = static_cast<OpenGLMesh *>(pipelineData->meshes[i].get());

            if (!p_MeshManager->Draw(pipelineData->shader.get(), openGLMesh, textures, materials, textureCount, materialCount))
            {
                Picasso::Engine::Logger::Logger::Error("[OpenGLGraphicsPipeline] unable to draw the mesh");

                delete[] textures;
                delete[] materials;
                return false;
            }
        }

        delete[] textures;
        delete[] materials;

        return true;
    }

    /**
     * @brief Ends the rendering process for the OpenGL graphics render.
     *
     * @param pipelineData The pipeline data containing the shader and other data.
     */
    void OpenGLGraphicsRender::EndRenderFrame(const Pipeline::PipelineData *pipelineData)
    {
        pipelineData->shader->Destroy();
    }

    /**
     * Sets the uniforms for rendering using the provided pipeline data.
     *
     * @param pipelineData A pointer to the PipelineData object containing the necessary data for rendering.
     */
    void OpenGLGraphicsRender::_UpdateData(const Pipeline::PipelineData *pipelineData)
    {
        std::vector<Picasso::Engine::EventSystem::PEventData> deferredRenderEvents =
            Picasso::Engine::EventSystem::DeferredEventsStore::Instance->Consume(Picasso::Engine::EventSystem::PEvent::RENDERER_UPDATE);

        if (deferredRenderEvents.size() == 0)
        {
            return;
        }

        float px, py, pz, rx, ry, rz;
        float sx, sy, sz;

        for (Picasso::Engine::EventSystem::PEventData eData : deferredRenderEvents)
        {
            px = eData.data.f[0];
            py = eData.data.f[1];
            pz = eData.data.f[2];
            rx = eData.data.f[3];
            ry = eData.data.f[4];
            rz = eData.data.f[5];
            sx = eData.data.f[6];
            sy = eData.data.f[7];
            sz = eData.data.f[8];

            for (int i = 0; i < pipelineData->meshes.size(); ++i)
            {
                OpenGLMesh *openGLMesh = static_cast<OpenGLMesh *>(pipelineData->meshes[i].get());

                p_MeshManager->UpdateModelMatrix(openGLMesh, px, py, pz, rx, ry, rz, sx, sy, sz);
            }

            // reset the coordinates
            px = py = pz = rx = ry = rz = sx = sy = sz = 0.0f;
        }
    }
}