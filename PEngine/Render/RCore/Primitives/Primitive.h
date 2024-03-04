#pragma once

#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <PEngine/Render/RCore/Vertex.h>

#include <vector>

namespace Picasso::Engine::Render::Core::Primitives
{
    class Primitive
    {
    public:
        virtual ~Primitive(){};

        inline const std::vector<Vertex> GetVertices() const { return m_Vertices; }
        inline const unsigned int GetVertexCount() const { return m_Vertices.size(); }
        inline const std::vector<unsigned int> GetIndices() const { return m_Indices; }
        inline const unsigned int GetIndexCount() const { return m_Indices.size(); }

    protected:
        std::vector<Vertex> m_Vertices;
        std::vector<unsigned int> m_Indices;

        void _Setup(const Vertex *vertices, unsigned int vertexCount, const unsigned int *indices, unsigned int indexCount);
    };
}

#endif // PRIMITIVE_H