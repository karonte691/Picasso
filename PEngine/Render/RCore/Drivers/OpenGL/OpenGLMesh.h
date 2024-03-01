#pragma once

#ifndef OPENGL_MESH_H
#define OPENGL_MESH_H

#include <PEngine/Render/RCore/Mesh.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLMatrixManager.h>

#include <Glew/glew.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <memory>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    class OpenGLMesh : public Mesh
    {
    public:
        OpenGLMesh(OpenGLMatrixManager *matrixManager)
            : p_MatrixManager(matrixManager) {}

        bool Create(std::vector<Vertex> vertices,
                    std::vector<unsigned int> indices,
                    const Math::Vector3 position,
                    const Math::Vector3 rotation,
                    const Math::Vector3 scale) override;
        bool Draw(Shader *shader, std::vector<Texture *> textures, std::vector<Material> materials) override;
        void Destroy();

    private:
        GLuint m_VAO;
        GLuint m_VBO;
        GLuint m_EBO;
        OpenGLMatrixManager *p_MatrixManager;

        bool _SetupVAO(std::vector<Vertex> vertices,
                       std::vector<unsigned int> indices);
        void _UniformMatrices(Shader *shader);
    };
}

#endif // OPENGL_MESH_H