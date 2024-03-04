#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLMesh.h>

#include <PEngine/Logger/Logger.h>

#include <PEngine/Render/RCore/Shader.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    void OpenGLMesh::InitModelMatrix(const Math::Vector3 &translate, const Math::Vector3 &rotation, const Math::Vector3 &scale)
    {
        p_ModelMatrix = Math::Mat4::Identity();
        p_ModelMatrix->Translate(translate);
        p_ModelMatrix->Rotate(Math::Mat4Rotation::X, rotation.x);
        p_ModelMatrix->Rotate(Math::Mat4Rotation::Y, rotation.y);
        p_ModelMatrix->Rotate(Math::Mat4Rotation::Z, rotation.z);
        p_ModelMatrix->Scale(scale);
    }

    void OpenGLMesh::UniformModelMatrix(const Core::Shader *shader)
    {
        glUniformMatrix4fv(glGetUniformLocation(shader->GetId(), "ModelMatrix"), 1, GL_FALSE, &p_ModelMatrix->m[0]);
    }

} // namespace Picasso::Engine::Render::Core::Drivers::OpenGL