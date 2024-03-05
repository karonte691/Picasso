#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLGraphicsPipeline.h>

#include <PEngine/Math/Vector3.h>
#include <PEngine/Math/PMath.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLError.h>
#include <PEngine/Render/RCore/Primitives/Quad.h>

#include <vector>
#include <string>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    /**
     * @brief Initializes the OpenGL graphics pipeline.
     *
     * This function initializes various components of the graphics pipeline, such as the texture manager,
     * VP matrix manager, light manager, pipeline data builder, material manager, and mesh manager.
     * It also creates the view matrix and projection matrix based on the provided API data.
     * Additionally, it sets the light position and checks if the pipeline data is successfully built.
     * Finally, it sets the uniform variables for the view matrix, projection matrix, camera position, and light position.
     *
     * @param apiData A pointer to the RAPIData structure containing API data.
     * @return True if the initialization is successful, false otherwise.
     */
    bool OpenGLGraphicsPipeline::Init(RAPIData *apiData)
    {
        p_TextureManager = std::make_unique<OpenGLTextureManager>();
        p_VPMatrixManager = std::make_unique<OpenGLVPMatrixManager>();
        p_LightManager = std::make_unique<OpenGLLightManager>();
        p_PipelineDataBuilder = std::make_unique<OpenGLPipelineDataBuilderManager>();
        p_MaterialManager = std::make_unique<OpenGLMaterialManager>();
        p_MeshManager = std::make_unique<OpenGLMeshManager>();

        p_VPMatrixManager->CreateViewMatrix();

        float fWidth = static_cast<float>(apiData->pState->width);
        float fHeight = static_cast<float>(apiData->pState->height);
        p_VPMatrixManager->CreateProjectionMatrix(fWidth, fHeight);

        // lights
        p_LightManager->SetLightPosition(Math::Vector3(0.0f, 0.0f, 1.0f));

        if (!p_PipelineDataBuilder->Build())
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLGraphicsPipeline] unable to build the pipeline data");
            return false;
        }

        m_PipelineData = p_PipelineDataBuilder->Get();

        p_VPMatrixManager->UniformViewMatrix(m_PipelineData.shaders[0]->GetId());
        p_VPMatrixManager->UniforProjectionMatrix(m_PipelineData.shaders[0]->GetId());
        p_VPMatrixManager->UniformCameraPosition(m_PipelineData.shaders[0]->GetId());
        p_LightManager->UniformLightPosition(m_PipelineData.shaders[0]->GetId());

        return true;
    }

    void OpenGLGraphicsPipeline::Shutdown()
    {
        m_PipelineData.shaders[0]->Destroy();
    }

    void OpenGLGraphicsPipeline::RegisterHooks()
    {
        PicassoRegistry::Subscribe(PEvent::RENDERER_UPDATE, [this](BaseEvent<PEvent> *&event)
                                   { this->_onRenderUpdate(event); });
    }

    bool OpenGLGraphicsPipeline::BeginFrame(RAPIData *apiData, float deltaTime, PPlatformState *pState)
    {
        if (!p_Driver->BeginFrame(apiData, deltaTime, pState))
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLGraphicsPipeline] driver function begin frame returned error");
            return false;
        }

        m_PipelineData.shaders[0]->Use();

        int textureCount = m_PipelineData.textures.size();
        int materialCount = m_PipelineData.materials.size();
        Texture **textures = new Texture *[textureCount];
        Material **materials = new Material *[materialCount];

        for (int i = 0; i < textureCount; ++i)
        {
            textures[i] = m_PipelineData.textures[i].get();
        }
        for (int i = 0; i < materialCount; ++i)
        {
            materials[i] = m_PipelineData.materials[i].get();
        }

        p_VPMatrixManager->UniformViewMatrix(m_PipelineData.shaders[0]->GetId());
        p_VPMatrixManager->UniforProjectionMatrix(m_PipelineData.shaders[0]->GetId());

        if (!p_TextureManager->ActivateTextures(m_PipelineData.shaders[0]->GetId(), textures, textureCount))
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLGraphicsPipeline] unable to activate textures");
            delete[] textures;
            delete[] materials;
            return false;
        }

        for (unsigned int i = 0; i < m_PipelineData.materials.size(); ++i)
        {
            p_MaterialManager->SendMaterialToShader(m_PipelineData.materials[i].get(), m_PipelineData.shaders[0].get());
        }

        for (unsigned int i = 0; i < m_PipelineData.meshes.size(); ++i)
        {
            OpenGLMesh *openGLMesh = static_cast<OpenGLMesh *>(m_PipelineData.meshes[i].get());

            if (!p_MeshManager->Draw(m_PipelineData.shaders[0].get(), openGLMesh, textures, materials, textureCount, materialCount))
            {
                Picasso::Engine::Logger::Logger::Error("[OpenGLGraphicsPipeline] unable to draw the mesh");

                delete[] textures;
                delete[] materials;
                return false;
            }

            delete[] textures;
            delete[] materials;
        }

        return true;
    }

    bool OpenGLGraphicsPipeline::EndFrame(RAPIData *apiData, float deltaTime, PPlatformState *pState)
    {
        m_PipelineData.shaders[0]->Destroy();
        return p_Driver->EndFrame(apiData, deltaTime, pState);
    }

    bool OpenGLGraphicsPipeline::Resize(u_int16_t width, u_int16_t height)
    {
        float fWidth = static_cast<float>(width);
        float fHeight = static_cast<float>(height);

        p_VPMatrixManager->ResetProjectionMatrix(fWidth, fHeight);

        return true;
    }

    void OpenGLGraphicsPipeline::_onRenderUpdate(BaseEvent<PEvent> *&event)
    {
        EventSystem::Events::PEventData eData = event->GetData();

        Picasso::Engine::Logger::Logger::Debug("OpenGLGraphicsPipeline: Updating renderer matrices");

        float px, py, pz, rx, ry, rz;
        float sx, sy, sz;

        px = eData.data.f[0];
        py = eData.data.f[1];
        pz = eData.data.f[2];
        rx = eData.data.f[3];
        ry = eData.data.f[4];
        rz = eData.data.f[5];
        sx = eData.data.f[6];
        sy = eData.data.f[7];
        sz = eData.data.f[8];

        for (int i = 0; i < m_PipelineData.meshes.size(); ++i)
        {
            OpenGLMesh *openGLMesh = static_cast<OpenGLMesh *>(m_PipelineData.meshes[i].get());

            p_MeshManager->UpdateModelMatrix(openGLMesh, px, py, pz, rx, ry, rz, sx, sy, sz);
        }
    }

}