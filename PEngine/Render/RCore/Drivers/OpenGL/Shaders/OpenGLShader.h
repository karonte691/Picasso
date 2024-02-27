#pragma once

#ifndef OPEN_GL_SHADER_H
#define OPEN_GL_SHADER_H

#include <PEngine/Logger/Logger.h>
#include <PEngine/Render/RCore/Shader.h>

#include <Glew/glew.h>
#include <GL/gl.h>
#include <GL/glx.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL::Shaders
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(GLuint id);

        GLuint GetId() { return m_Id; };

        void Use() override;
        void Clear() override;
        void Destroy() override;

        void SetVector(const char *name, const float value) override;
        void SetVector(const char *name, const Math::Vector2 value) override;
        void SetVector(const char *name, const Math::Vector3 value) override;
        void SetVector(const char *name, const Math::Vector4 value) override;

        void SetMatrix(const char *name, const Math::Mat4 value) override;
        void setTexture(const char *name, const int value) override;

    private:
        GLuint m_Id;
    };
}

#endif