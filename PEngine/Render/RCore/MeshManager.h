#pragma once

#ifndef MESH_MANAGER_H
#define MESH_MANAGER_H

#include <PEngine/Render/RCore/Vertex.h>
#include <PEngine/Render/RCore/Shader.h>
#include <PEngine/Render/RCore/Texture.h>
#include <PEngine/Render/RCore/Material.h>
#include <PEngine/Render/RCore/Material.h>
#include <PEngine/Render/RCore/Primitives/Primitive.h>
#include <PEngine/Math/Vector3.h>
#include <PEngine/Render/RCore/Mesh.h>
#include <vector>
#include <memory>

namespace Picasso::Engine::Render::Core
{
    class MeshManager
    {
    public:
        virtual ~MeshManager(){};
    };
}

#endif // MESH_MANAGER_H