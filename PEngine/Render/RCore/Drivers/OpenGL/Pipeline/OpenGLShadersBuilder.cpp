#include <PEngine/Render/RCore/Drivers/OpenGL/Pipeline/OpenGLShadersBuilder.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    OpenGLShadersBuilder::OpenGLShadersBuilder()
    {
        p_FileLoader = std::make_unique<File::PFLoader>();
        p_ShaderFactory = std::make_unique<Drivers::OpenGL::Shaders::OpenGLShaderFactory>();
    }

    /**
     * Builds the OpenGL shaders for the given pipeline data.
     *
     * @param pipelineData A pointer to the PipelineData object.
     * @return True if the shaders were successfully built, false otherwise.
     */
    bool OpenGLShadersBuilder::Build(Pipeline::PipelineData *pipelineData)
    {
        File::PFile vertexShader = p_FileLoader->LoadShader("VertexCore.glsl");
        File::PFile fragmentShader = p_FileLoader->LoadShader("FragmentCore.glsl");

        if (vertexShader.fileName == "" || fragmentShader.fileName == "")
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLShadersBuilder] unable to open the core shaders");
            return false;
        }

        std::unique_ptr<Shader> pShader = p_ShaderFactory->Create(vertexShader.content, fragmentShader.content);

        if (pShader == nullptr)
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLShadersBuilder] unable to create the shader");
            return false;
        }

        pipelineData->shaders.push_back(std::move(pShader));

        return true;
    }
}