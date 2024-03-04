#pragma once

#ifndef MESH_H
#define MESH_H

namespace Picasso::Engine::Render::Core
{
    // Each driver has its own implementation of Mesh
    class Mesh
    {
    public:
        virtual ~Mesh(){};

        unsigned int getVertexCount() const
        {
            return m_VertexCount;
        }

        void setVertexCount(unsigned int newVertexCount)
        {
            m_VertexCount = newVertexCount;
        }

        unsigned int getIndexCount() const
        {
            return m_IndexCount;
        }

        void setIndexCount(unsigned int newIndexCount)
        {
            m_IndexCount = newIndexCount;
        }

    protected:
        unsigned int m_VertexCount;
        unsigned int m_IndexCount;
    };
}

#endif // MESH_H