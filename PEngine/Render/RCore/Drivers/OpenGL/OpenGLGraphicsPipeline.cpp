#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLGraphicsPipeline.h>

#include <PEngine/Math/Vector3.h>
#include <PEngine/Math/PMath.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLError.h>

#include <vector>
#include <string>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    bool OpenGLGraphicsPipeline::Init(RAPIData *apiData)
    {
        p_FileLoader = std::make_unique<Picasso::Engine::File::PFLoader>();
        p_ShaderFactory = std::make_unique<Shaders::OpenGLShaderFactory>();
        p_TextureManager = std::make_unique<OpenGLTextureManager>();
        p_MatrixManager = std::make_unique<OpenGLMatrixManager>();
        p_Mesh = std::make_unique<OpenGLMesh>(p_MatrixManager.get());
        p_LightManager = std::make_unique<OpenGLLightManager>();
        p_MaterialManager = std::make_unique<OpenGLMaterialManager>();

        m_Vertices[0] = Vertex{
            Math::Vector3(-0.5f, 0.5f, 0.0f),
            Math::Vector3(1.0f, 0.0f, 0.0f),
            Math::Vector2(0.0f, 1.0f),
            Math::Vector3(0.0f, 0.0f, -1.0f)};
        m_Vertices[1] = Vertex{
            Math::Vector3(-0.5f, -0.5f, 0.0f),
            Math::Vector3(0.0f, 1.0f, 0.0f),
            Math::Vector2(0.0f, 0.0f),
            Math::Vector3(0.0f, 0.0f, -1.0f)};
        m_Vertices[2] = Vertex{
            Math::Vector3(0.5f, -0.5f, 0.0f),
            Math::Vector3(0.0f, 0.0f, 1.0f),
            Math::Vector2(1.0f, 0.0f),
            Math::Vector3(0.0f, 0.0f, -1.0f)};
        m_Vertices[3] = Vertex{
            Math::Vector3(0.5f, 0.5f, 0.0f),
            Math::Vector3(1.0f, 1.0f, 0.0f),
            Math::Vector2(1.0f, 1.0f),
            Math::Vector3(0.0f, 0.0f, -1.0f)};

        m_Indices[0] = 0;
        m_Indices[1] = 1;
        m_Indices[2] = 2;
        m_Indices[3] = 0;
        m_Indices[4] = 2;
        m_Indices[5] = 3;

        File::PFile vertexShader = p_FileLoader->LoadShader("VertexCore.glsl");
        File::PFile fragmentShader = p_FileLoader->LoadShader("FragmentCore.glsl");

        if (vertexShader.fileName == "" || fragmentShader.fileName == "")
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLGraphicsPipeline] unable to open the core shaders");
            return false;
        }

        p_Shader = p_ShaderFactory->Create(vertexShader.content, fragmentShader.content);

        if (p_Shader == nullptr)
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLGraphicsPipeline] unable to create the shader");
            return false;
        }

        std::vector<std::string> texturesToLoad;

        // texturesToLoad.push_back("bg.png");
        texturesToLoad.push_back("pngegg.png");

        // texture
        if (!p_TextureManager->LoadTextures(texturesToLoad))
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLGraphicsPipeline] Unable to load the texture");

            return false;
        }

        m_Textures = p_TextureManager->GetTextures();

        // materials
        for (Texture *texture : m_Textures)
        {
            Material material = p_MaterialManager->CreateMaterial(
                Math::Vector3(0.1f, 0.1f, 0.1f),
                Math::Vector3(1.0f, 1.0f, 1.0f),
                Math::Vector3(1.0f, 1.0f, 1.0f),
                50.0f,
                texture, texture);

            if (material.DiffuseTexture == nullptr || material.SpecularTexture == nullptr)
            {
                Picasso::Engine::Logger::Logger::Error("[OpenGLGraphicsPipeline] material textures are null");
                return false;
            }

            if (material.DiffuseTexture->Id == 0 || material.SpecularTexture->Id == 0)
            {
                Picasso::Engine::Logger::Logger::Error("[OpenGLGraphicsPipeline] material textures are null");
                return false;
            }

            m_Materials.push_back(material);
        }

        p_Shader->Use();

        std::vector<Vertex> vertices(std::begin(m_Vertices), std::end(m_Vertices));
        std::vector<unsigned int> indices(std::begin(m_Indices), std::end(m_Indices));

        // matrices
        if (!p_Mesh->Create(vertices, indices, Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(1.0f, 1.0f, 1.0f)))
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLGraphicsPipeline] unable to create the mesh");
            return false;
        }

        p_MatrixManager->CreateViewMatrix();

        float fWidth = static_cast<float>(apiData->pState->width);
        float fHeight = static_cast<float>(apiData->pState->height);
        p_MatrixManager->CreateProjectionMatrix(fWidth, fHeight);

        // lights
        p_LightManager->SetLightPosition(Math::Vector3(0.0f, 0.0f, 1.0f));

        p_MatrixManager->UniformViewMatrix(p_Shader->GetId());
        p_MatrixManager->UniforProjectionMatrix(p_Shader->GetId());
        p_MatrixManager->UniformCameraPosition(p_Shader->GetId());
        p_LightManager->UniformLightPosition(p_Shader->GetId());

        return true;
    }

    void OpenGLGraphicsPipeline::Shutdown()
    {
        p_Shader->Destroy();
        p_Mesh->Destroy();
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

        p_Shader->Use();

        p_MatrixManager->UniformViewMatrix(p_Shader->GetId());
        p_MatrixManager->UniforProjectionMatrix(p_Shader->GetId());

        if (!p_TextureManager->ActivateTextures(p_Shader->GetId()))
        {
            return false;
        }

        for (Material material : m_Materials)
        {
            p_MaterialManager->SendMaterialToShader(material, p_Shader.get());
        }

        if (!p_Mesh->Draw(p_Shader.get(), m_Textures, m_Materials))
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLGraphicsPipeline] unable to draw the mesh");
            return false;
        }

        return true;
    }

    bool OpenGLGraphicsPipeline::EndFrame(RAPIData *apiData, float deltaTime, PPlatformState *pState)
    {
        p_Shader->Destroy();
        return p_Driver->EndFrame(apiData, deltaTime, pState);
    }

    bool OpenGLGraphicsPipeline::Resize(u_int16_t width, u_int16_t height)
    {
        float fWidth = static_cast<float>(width);
        float fHeight = static_cast<float>(height);

        p_MatrixManager->ResetProjectionMatrix(fWidth, fHeight);

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

        p_MatrixManager->UpdateModelMatrix(px, py, pz, rx, ry, rz, sx, sy, sz);
    }
}