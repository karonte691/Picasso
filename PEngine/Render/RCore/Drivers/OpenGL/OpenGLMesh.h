#pragma once

#ifndef OPEN_GL_MESH_H
#define OPEN_GL_MESH_H

#include <PEngine/Render/RCore/Mesh.h>
#include <PEngine/Render/RCore/Shader.h>
#include <PEngine/Math/Mat4.h>
#include <PEngine/Math/Vector3.h>
#include <Glew/glew.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <memory>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    class OpenGLMesh : public Mesh
    {
    public:
        GLuint VAO;
        GLuint VBO;
        GLuint EBO;

        void InitModelMatrix(const Math::Vector3 &translate, const Math::Vector3 &rotation, const Math::Vector3 &scale);
        void UniformModelMatrix(const Shader *shader);

    private:
        std::unique_ptr<Math::Mat4> p_ModelMatrix;
    };
}

#endif // OPEN_GL_MESH_H