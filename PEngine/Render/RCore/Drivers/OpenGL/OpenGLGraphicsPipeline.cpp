#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLGraphicsPipeline.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    OpenGLGraphicsPipeline::~OpenGLGraphicsPipeline()
    {
        if (p_FileLoader != nullptr)
        {
            delete p_FileLoader;
            p_FileLoader = nullptr;
        }

        if (p_ShaderFactory != nullptr)
        {
            delete p_ShaderFactory;
            p_ShaderFactory = nullptr;
        }
    }

    bool OpenGLGraphicsPipeline::BeginFrame(RAPIData *apiData, _Float32 deltaTime, PPlatformState *pState)
    {
        if (!m_PipelineStarted)
        {
            // start the pipeline
            m_PipelineStarted = this->_initPipeline();
        }

        if (!p_Driver->BeginFrame(apiData, deltaTime, pState))
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLGraphicsPipeline] driver function begin frame returned error");
            return false;
        }

        File::PFile vertexShader = p_FileLoader->LoadShader("VertexCore.glsl");
        File::PFile fragmentShader = p_FileLoader->LoadShader("FragmentCore.glsl");

        if (vertexShader.fileName == "" || fragmentShader.fileName == "")
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLGraphicsPipeline] unable to open the core shaders");
            return false;
        }

        std::unique_ptr<Shaders::OpenGLShader> shader = p_ShaderFactory->Create(vertexShader.content, fragmentShader.content);

        if (shader == nullptr)
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLGraphicsPipeline] unable to create the shader");
            return false;
        }

        shader->Use();
        shader->Destroy();

        return true;
    }

    bool OpenGLGraphicsPipeline::EndFrame(RAPIData *apiData, _Float32 deltaTime, PPlatformState *pState)
    {
        return p_Driver->EndFrame(apiData, deltaTime, pState);
    }

    bool OpenGLGraphicsPipeline::_initPipeline()
    {
        if (p_FileLoader == nullptr)
        {
            p_FileLoader = new Picasso::Engine::File::PFLoader();
        }

        if (p_ShaderFactory == nullptr)
        {
            p_ShaderFactory = new Shaders::OpenGLShaderFactory();
        }

        return true;
    }
}