#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLMesh.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLError.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    bool OpenGLMesh::Create(std::vector<Vertex> vertexList, std::vector<unsigned int> indices, const Math::Vector3 position, const Math::Vector3 rotation, const Math::Vector3 scale)
    {
        if (!_SetupVAO(vertexList, indices))
        {
            return false;
        }

        p_MatrixManager->CreateModelMatrix(position, rotation, scale);

        return true;
    }

    bool OpenGLMesh::Draw(Shader *shader, std::vector<Texture *> textures, std::vector<Material> materials)
    {
        _UniformMatrices(shader);

        CHECK_GL_ERROR(glBindVertexArray(m_VAO));

        if (m_IndexCount == 0)
        {
            CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, m_VertexCount, GL_UNSIGNED_INT, 0));

            return true;
        }

        CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0));

        return true;
    }

    void OpenGLMesh::Destroy()
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
    }

    bool OpenGLMesh::_SetupVAO(std::vector<Vertex> vertices,
                               std::vector<unsigned int> indices)
    {
        m_VertexCount = vertices.size();
        m_IndexCount = indices.size();

        if (m_VertexCount == 0)
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLMesh] vertex count is 0");
            return false;
        }

        CHECK_GL_ERROR(glCreateVertexArrays(1, &m_VAO));
        CHECK_GL_ERROR(glBindVertexArray(m_VAO));

        CHECK_GL_ERROR(glGenBuffers(1, &m_VBO));
        CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
        CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_VertexCount, vertices.data(), GL_STATIC_DRAW));

        CHECK_GL_ERROR(glGenBuffers(1, &m_EBO));
        CHECK_GL_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO));
        CHECK_GL_ERROR(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_IndexCount, indices.data(), GL_STATIC_DRAW));

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

    void OpenGLMesh::_UniformMatrices(Shader *shader)
    {
        p_MatrixManager->UniformModelMatrix(shader->GetId());
    }
} // namespace Picasso::Engine::Render::Core::Drivers::OpenGL