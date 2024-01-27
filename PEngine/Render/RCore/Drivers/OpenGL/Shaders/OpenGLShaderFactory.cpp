#include <PEngine/Render/RCore/Drivers/OpenGL/Shaders/OpenGLShaderFactory.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL::Shaders
{
    std::shared_ptr<OpenGLShader> OpenGLShaderFactory::Create(std::string vertexContent, std::string fragmentContent)
    {
        ShaderModule vertexModule = this->_createShaderModule(vertexContent, GL_VERTEX_SHADER);

        if (!vertexModule.Compiled)
        {
            return nullptr;
        }

        ShaderModule fragmentModule = this->_createShaderModule(fragmentContent, GL_FRAGMENT_SHADER);

        if (!fragmentModule.Compiled)
        {
            return nullptr;
        }

        GLuint shaderId = glCreateProgram();

        glAttachShader(shaderId, vertexModule.Id);
        glAttachShader(shaderId, fragmentModule.Id);

        glLinkProgram(shaderId);

        int shaderLinkingSuccess = 0;
        glGetProgramiv(shaderId, GL_LINK_STATUS, &shaderLinkingSuccess);

        if (!shaderLinkingSuccess)
        {
            GLint logLength = 0;
            glGetProgramiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);

            if (logLength > 1)
            {
                std::vector<GLchar> errorLog(logLength);
                glGetShaderInfoLog(shaderId, logLength, 0, &errorLog[0]);

                Picasso::Engine::Logger::Logger::Error("Cannot link shader: %s", errorLog.data());
            }

            return nullptr;
        }

        glDeleteShader(vertexModule.Id);
        glDeleteShader(fragmentModule.Id);

        return std::make_shared<OpenGLShader>(shaderId);
    }

    ShaderModule OpenGLShaderFactory::_createShaderModule(std::string shaderContent, GLuint shaderType)
    {
        GLuint shaderModule = glCreateShader(shaderType);
        const char *sharedSrc = shaderContent.c_str();
        ShaderModule shdModule = {};

        glShaderSource(shaderModule, 1, &sharedSrc, 0);
        glCompileShader(shaderModule);

        int shaderCompilationSuccess = 0;
        glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &shaderCompilationSuccess);

        if (!shaderCompilationSuccess)
        {
            GLint logLength = 0;
            glGetShaderiv(shaderModule, GL_INFO_LOG_LENGTH, &logLength);

            if (logLength > 1)
            {
                std::vector<GLchar> errorLog(logLength);
                glGetShaderInfoLog(shaderModule, logLength, 0, &errorLog[0]);

                Picasso::Engine::Logger::Logger::Error("Cannot compile shader: %s", errorLog.data());
            }

            return shdModule;
        }

        shdModule.Id = shaderModule;
        shdModule.Compiled = true;

        return shdModule;
    }
}