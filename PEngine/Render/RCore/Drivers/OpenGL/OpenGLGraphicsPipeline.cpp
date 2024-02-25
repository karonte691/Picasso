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

        m_Vertices[0] = Vertex{
            Math::Vector3(-0.5f, 0.5f, 0.0f),
            Math::Vector3(1.0f, 0.0f, 0.0f),
            Math::Vector2(0.0f, 1.0f)};
        m_Vertices[1] = Vertex{
            Math::Vector3(-0.5f, -0.5f, 0.0f),
            Math::Vector3(0.0f, 1.0f, 0.0f),
            Math::Vector2(0.0f, 0.0f)};
        m_Vertices[2] = Vertex{
            Math::Vector3(0.5f, -0.5f, 0.0f),
            Math::Vector3(0.0f, 0.0f, 1.0f),
            Math::Vector2(1.0f, 0.0f)};
        m_Vertices[3] = Vertex{
            Math::Vector3(0.5f, 0.5f, 0.0f),
            Math::Vector3(1.0f, 1.0f, 0.0f),
            Math::Vector2(1.0f, 1.0f)};

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

        CHECK_GL_ERROR(glCreateVertexArrays(1, &m_VAD));
        CHECK_GL_ERROR(glBindVertexArray(m_VAD));

        CHECK_GL_ERROR(glGenBuffers(1, &m_VB0));
        CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, m_VB0));
        CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices, GL_STATIC_DRAW));

        CHECK_GL_ERROR(glGenBuffers(1, &m_EBO));
        CHECK_GL_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO));
        CHECK_GL_ERROR(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_Indices), m_Indices, GL_STATIC_DRAW));

        // position
        CHECK_GL_ERROR(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, position)));
        CHECK_GL_ERROR(glEnableVertexAttribArray(0));
        // color
        CHECK_GL_ERROR(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, color)));
        CHECK_GL_ERROR(glEnableVertexAttribArray(1));
        // texcoord
        CHECK_GL_ERROR(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, texcoord)));
        CHECK_GL_ERROR(glEnableVertexAttribArray(2));

        glBindVertexArray(0);

        std::vector<std::string> texturesToLoad;

        // texturesToLoad.push_back("bg.png");
        texturesToLoad.push_back("pngegg.png");

        // texture
        if (!p_TextureManager->LoadTextures(texturesToLoad))
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLGraphicsPipeline] Unable to load the texture");

            return false;
        }

        // matrices
        p_MatrixManager->CreateModelMatrix(Math::Vector3::Zero(), Math::Vector3::One());
        p_MatrixManager->CreateViewMatrix();

        float fWidth = static_cast<float>(apiData->pState->width);
        float fHeight = static_cast<float>(apiData->pState->height);
        p_MatrixManager->CreateProjectionMatrix(fWidth, fHeight);

        p_Shader->Use();

        p_MatrixManager->UniformMatrices(p_Shader->GetId());

        return true;
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

        if (!p_TextureManager->ActivateTextures(p_Shader->GetId()))
        {
            return false;
        }

        CHECK_GL_ERROR(glBindVertexArray(m_VAD));
        CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

        p_Shader->Use();

        p_MatrixManager->UniformMatrices(p_Shader->GetId());

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
        bool updateCameraPos = false;

        // update positions?
        if (eData.data.f32[0] != 0.0f || eData.data.f32[1] != 0.0f || eData.data.f32[2] != 0.0f)
        {
            px = eData.data.f32[0];
            py = eData.data.f32[1];
            pz = eData.data.f32[2];
            updateCameraPos = true;
        }

        // update rotations?
        if (eData.data.f32[3] != 0.0f || eData.data.f32[4] != 0.0f || eData.data.f32[5] != 0.0f)
        {
            rx = eData.data.f32[3];
            ry = eData.data.f32[4];
            rz = eData.data.f32[5];
            updateCameraPos = true;
        }

        if (updateCameraPos)
        {
            Picasso::Engine::Logger::Logger::Debug("[OpenGLGraphicsPipeline]px: %f, py: %f, pz: %f, rx: %f, ry: %f, rz: %f", px, py, pz, rx, ry, rz);
            p_MatrixManager->UpdateMatrices(px, py, pz, rx, ry, rz);
        }
    }
}