#include <PEngine/Render/RCore/Drivers/OpenGL/Shaders/OpenGLShader.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL::Shaders
{
    OpenGLShader::OpenGLShader(GLuint id)
    {
        m_Id = id;
    }

    void OpenGLShader::Use()
    {
        glUseProgram(m_Id);
    }

    void OpenGLShader::Destroy()
    {
        glDeleteProgram(m_Id);
    }
}