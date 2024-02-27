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
        Use();

        glUniform1f(glGetUniformLocation(m_Id, name), value);

        Clear();
    }

    void OpenGLShader::SetVector(const char *name, const Math::Vector2 value)
    {
        Use();

        glUniform2f(glGetUniformLocation(m_Id, name), value.x, value.y);

        Clear();
    }

    void OpenGLShader::SetVector(const char *name, const Math::Vector3 value)
    {
        Use();

        glUniform3f(glGetUniformLocation(m_Id, name), value.x, value.y, value.z);

        Clear();
    }

    void OpenGLShader::SetVector(const char *name, const Math::Vector4 value)
    {
        Use();

        glUniform4f(glGetUniformLocation(m_Id, name), value.x, value.y, value.z, value.w);

        Clear();
    }

    void OpenGLShader::SetMatrix(const char *name, const Math::Mat4 value)
    {
        Use();

        glUniformMatrix4fv(glGetUniformLocation(m_Id, name), 1, GL_FALSE, &value.m[0]);

        Clear();
    }

    void OpenGLShader::setTexture(const char *name, const int value)
    {
        Use();

        glUniform1i(glGetUniformLocation(m_Id, name), value);

        Clear();
    }
}