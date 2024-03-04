#pragma once

#ifndef OPENGL_MESH_MANAGER_H
#define OPENGL_MESH_MANAGER_H

#include <PEngine/Render/RCore/Mesh.h>
#include <PEngine/Render/RCore/MeshManager.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLVPMatrixManager.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLMesh.h>

#include <Glew/glew.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <memory>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    class OpenGLMeshManager : public MeshManager
    {
    public:
        std::unique_ptr<OpenGLMesh> Create(const Primitives::Primitive *primitive,
                                           const Math::Vector3 position,
                                           const Math::Vector3 rotation,
                                           const Math::Vector3 scale);
        bool Draw(const Shader *shader,
                  OpenGLMesh *mesh,
                  Texture **textures,
                  Material **materials,
                  unsigned int textureCount,
                  unsigned int materialCount);
        void Destroy(OpenGLMesh *mesh);

        void UpdateModelMatrix(OpenGLMesh *mesh, float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz);

    private:
        std::unique_ptr<Math::Mat4> p_ModelMatrix;

        bool _SetupVAO(const Primitives::Primitive *primitive, OpenGLMesh *mesh);
        void _CreateModelMatrix(OpenGLMesh *mesh, const Math::Vector3 &translate, const Math::Vector3 &rotation, const Math::Vector3 &scale);
        void _UniformModelMatrix(const Shader *shader, OpenGLMesh *mesh);
    };
}

#endif // OPENGL_MESH_MANAGER_H