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

    void OpenGLShader::Clear()
    {
        glUseProgram(0);
    }

    void OpenGLShader::Destroy()
    {
        glDeleteProgram(m_Id);
    }

    void OpenGLShader::SetVector(const char *name, const float value)
    {
        glUniform1f(glGetUniformLocation(m_Id, name), value);
    }

    void OpenGLShader::SetVector(const char *name, const Math::Vector2 value)
    {
        glUniform2f(glGetUniformLocation(m_Id, name), value.x, value.y);
    }

    void OpenGLShader::SetVector(const char *name, const Math::Vector3 value)
    {
        glUniform3f(glGetUniformLocation(m_Id, name), value.x, value.y, value.z);
    }

    void OpenGLShader::SetVector(const char *name, const Math::Vector4 value)
    {
        glUniform4f(glGetUniformLocation(m_Id, name), value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::SetMatrix(const char *name, const Math::Mat4 value)
    {
        glUniformMatrix4fv(glGetUniformLocation(m_Id, name), 1, GL_FALSE, &value.m[0]);
    }

    void OpenGLShader::setTexture(const char *name, const int value)
    {
        glUniform1i(glGetUniformLocation(m_Id, name), value);
    }
}