#pragma once

#ifndef MESH_H
#define MESH_H

#include <PEngine/Render/RCore/Vertex.h>
#include <PEngine/Render/RCore/Shader.h>
#include <PEngine/Render/RCore/Texture.h>
#include <PEngine/Render/RCore/Material.h>
#include <PEngine/Math/Vector3.h>

#include <vector>

namespace Picasso::Engine::Render::Core
{
    class Mesh
    {
    public:
        virtual ~Mesh(){};

        virtual bool Create(std::vector<Vertex> vertices,
                            std::vector<unsigned int> indices,
                            const Math::Vector3 position,
                            const Math::Vector3 rotation,
                            const Math::Vector3 scale) = 0;
        virtual bool Draw(Shader *shader, std::vector<Texture *> textures, std::vector<Material> materials) = 0;
        virtual void Destroy() = 0;

    protected:
        unsigned int m_VertexCount;
        unsigned int m_IndexCount;
    };
}

#endif // MESH_H