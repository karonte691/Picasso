#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLMeshManager.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLError.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    std::unique_ptr<OpenGLMesh> OpenGLMeshManager::Create(const Primitives::Primitive *primitive,
                                                          const Math::Vector3 position,
                                                          const Math::Vector3 rotation,
                                                          const Math::Vector3 scale)
    {
        std::unique_ptr<OpenGLMesh> mesh = std::make_unique<OpenGLMesh>();

        if (!_SetupVAO(primitive, mesh.get()))
        {
            return nullptr;
        }

        mesh->InitModelMatrix(position, rotation, scale);

        return mesh;
    }

    /**
     * Draws a mesh using the specified shader, textures, and materials.
     *
     * @param shader The shader to use for rendering.
     * @param mesh The mesh to be drawn.
     * @param textures An array of textures to be applied to the mesh.
     * @param materials An array of materials to be applied to the mesh.
     * @param textureCount The number of textures in the textures array.
     * @param materialCount The number of materials in the materials array.
     * @return True if the mesh was successfully drawn, false otherwise.
     */
    bool OpenGLMeshManager::Draw(const Shader *shader,
                                 OpenGLMesh *mesh,
                                 Texture **textures,
                                 Material **materials,
                                 unsigned int textureCount,
                                 unsigned int materialCount)
    {
        _UniformModelMatrix(shader, mesh);

        CHECK_GL_ERROR(glBindVertexArray(mesh->VAO));

        if (mesh->getIndexCount() == 0)
        {
            CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, mesh->getVertexCount(), GL_UNSIGNED_INT, 0));

            return true;
        }

        CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, mesh->getIndexCount(), GL_UNSIGNED_INT, 0));

        return true;
    }

    void OpenGLMeshManager::Destroy(OpenGLMesh *mesh)
    {
        glDeleteVertexArrays(1, &mesh->VAO);
        glDeleteBuffers(1, &mesh->VBO);
        glDeleteBuffers(1, &mesh->EBO);
    }

    void OpenGLMeshManager::UpdateModelMatrix(OpenGLMesh *mesh, float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz)
    {
        _CreateModelMatrix(mesh, Math::Vector3(px, py, pz), Math::Vector3(rx, ry, rz), Math::Vector3(sx, sy, sz));
    }

    void OpenGLMeshManager::_CreateModelMatrix(OpenGLMesh *mesh, const Math::Vector3 &translate, const Math::Vector3 &rotation, const Math::Vector3 &scale)
    {
        mesh->InitModelMatrix(translate, rotation, scale);
    }

    bool OpenGLMeshManager::_SetupVAO(const Primitives::Primitive *primitive, OpenGLMesh *mesh)
    {
        mesh->setVertexCount(primitive->GetVertexCount());
        mesh->setIndexCount(primitive->GetIndexCount());

        if (mesh->getVertexCount() == 0)
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLMesh] vertex count is 0");
            return false;
        }

        CHECK_GL_ERROR(glCreateVertexArrays(1, &mesh->VAO));
        CHECK_GL_ERROR(glBindVertexArray(mesh->VAO));

        CHECK_GL_ERROR(glGenBuffers(1, &mesh->VBO));
        CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO));
        CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->getVertexCount(), primitive->GetVertices().data(), GL_STATIC_DRAW));

        CHECK_GL_ERROR(glGenBuffers(1, &mesh->EBO));
        CHECK_GL_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO));
        CHECK_GL_ERROR(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->getIndexCount(), primitive->GetIndices().data(), GL_STATIC_DRAW));

        // position
        CHECK_GL_ERROR(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, position)));
        CHECK_GL_ERROR(glEnableVertexAttribArray(0));
        // color
        CHECK_GL_ERROR(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, color)));
        CHECK_GL_ERROR(glEnableVertexAttribArray(1));
        // texcoord
        CHECK_GL_ERROR(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, texcoord)));
        CHECK_GL_ERROR(glEnableVertexAttribArray(2));
        // normal
        CHECK_GL_ERROR(glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, normal)));
        CHECK_GL_ERROR(glEnableVertexAttribArray(3));

        glBindVertexArray(0);

        return true;
    }

    void OpenGLMeshManager::_UniformModelMatrix(const Shader *shader, OpenGLMesh *mesh)
    {
        mesh->UniformModelMatrix(shader);
    }
} // namespace Picasso::Engine::Render::Core::Drivers::OpenGL