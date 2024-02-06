#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLGraphicsPipeline.h>

#include <PEngine/Math/Vector3.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    bool OpenGLGraphicsPipeline::Init()
    {
        p_FileLoader = std::make_unique<Picasso::Engine::File::PFLoader>();
        p_ShaderFactory = std::make_unique<Shaders::OpenGLShaderFactory>();

        m_Vertices[0] = Vertex{
            Math::Vector3(0.0f, 0.5f, 0.0f),
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

        m_Indices[0] = 0;
        m_Indices[1] = 1;
        m_Indices[2] = 2;

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

        glCreateVertexArrays(1, &m_VAD);
        glBindVertexArray(m_VAD);

        if (glGetError() != GL_NO_ERROR)
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLGraphicsPipeline] Error after creating and binding VAO");
            return false;
        }

        glGenBuffers(1, &m_VB0);
        glBindBuffer(GL_ARRAY_BUFFER, m_VB0);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices, GL_STATIC_DRAW);

        glGenBuffers(1, &m_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_Indices), m_Indices, GL_STATIC_DRAW);

        // position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, position));
        glEnableVertexAttribArray(0);
        // color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, color));
        glEnableVertexAttribArray(1);
        // texcoord
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, texcoord));
        glEnableVertexAttribArray(2);

        if (glGetError() != GL_NO_ERROR)
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLGraphicsPipeline] Error after setting vertex attribute pointers");
            return false;
        }

        glBindVertexArray(0);

        return true;
    }

    bool OpenGLGraphicsPipeline::BeginFrame(RAPIData *apiData, float deltaTime, PPlatformState *pState)
    {
        if (!p_Driver->BeginFrame(apiData, deltaTime, pState))
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLGraphicsPipeline] driver function begin frame returned error");
            return false;
        }

        p_Shader->Use();

        glBindVertexArray(m_VAD);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        GLenum error;
        while ((error = glGetError()) != GL_NO_ERROR)
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLGraphicsPipeline] OpenGL Error: %s ", std::to_string(error));
            return false;
        }

        return true;
    }

    bool OpenGLGraphicsPipeline::EndFrame(RAPIData *apiData, float deltaTime, PPlatformState *pState)
    {
        p_Shader->Destroy();
        return p_Driver->EndFrame(apiData, deltaTime, pState);
    }
}