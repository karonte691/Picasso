#include <PEngine/Render/RCore/Primitives/Primitive.h>

namespace Picasso::Engine::Render::Core::Primitives
{
    void Primitive::_Setup(const Vertex *vertices, unsigned int vertexCount, const unsigned int *indices, unsigned int indexCount)
    {
        m_Vertices.resize(vertexCount);
        m_Indices.resize(indexCount);

        for (unsigned int i = 0; i < vertexCount; i++)
        {
            m_Vertices[i] = vertices[i];
        }

        for (unsigned int i = 0; i < indexCount; i++)
        {
            m_Indices[i] = indices[i];
        }
    }
}