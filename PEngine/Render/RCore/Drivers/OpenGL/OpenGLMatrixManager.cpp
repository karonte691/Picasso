#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLMatrixManager.h>

#include <PEngine/Math/PMath.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    static const float FOV = 90.0f;
    static const float NEAR_PLANE = 0.1f;
    static const float FAR_PLANE = 1000.0f;

    void OpenGLMatrixManager::CreateModelMatrix(const Math::Vector3 &translate, const Math::Vector3 &scale)
    {
        p_ModelMatrix = Math::Mat4::Identity();
        p_ModelMatrix->Translate(translate);
        p_ModelMatrix->Scale(scale);
    }

    void OpenGLMatrixManager::RotateModelMatrixAxisX(float radians)
    {
        p_ModelMatrix->Rotate(Math::Mat4Rotation::X, radians);
    }

    void OpenGLMatrixManager::RotateModelMatrixAxisY(float radians)
    {
        p_ModelMatrix->Rotate(Math::Mat4Rotation::Y, radians);
    }

    void OpenGLMatrixManager::RotateModelMatrixAxisZ(float radians)
    {
        p_ModelMatrix->Rotate(Math::Mat4Rotation::Z, radians);
    }

    void OpenGLMatrixManager::UniformModelMatrix(GLuint shaderId)
    {
        glUniformMatrix4fv(glGetUniformLocation(shaderId, "ModelMatrix"), 1, GL_FALSE, &p_ModelMatrix->m[0]);
    }

    void OpenGLMatrixManager::CreateViewMatrix()
    {
        Math::Vector3 camPosition = Math::Vector3::Zero();
        Math::Vector3 worlUp(0.0f, 1.0f, 0.0f);
        Math::Vector3 camFront(0.0f, 0.0f, -1.0f);

        p_ViewMatrix = Math::Mat4::Identity();
        p_ViewMatrix->LookAt(camPosition, camPosition.Add(&camFront), worlUp);
    }

    void OpenGLMatrixManager::UniformViewMatrix(GLuint shaderId)
    {
        glUniformMatrix4fv(glGetUniformLocation(shaderId, "ViewMatrix"), 1, GL_FALSE, &p_ViewMatrix->m[0]);
    }

    void OpenGLMatrixManager::CreateProjectionMatrix(float width, float height)
    {
        _initProjectionMatrix(width, height);
    }

    void OpenGLMatrixManager::UniforProjectionMatrix(GLuint shaderId)
    {
        glUniformMatrix4fv(glGetUniformLocation(shaderId, "ProjectionMatrix"), 1, GL_FALSE, &p_ProjectionMatrix->m[0]);
    }

    void OpenGLMatrixManager::ResetProjectionMatrix(float width, float height)
    {
        _initProjectionMatrix(width, height);
    }

    void OpenGLMatrixManager::_initProjectionMatrix(float width, float height)
    {
        p_ProjectionMatrix = Math::Mat4::Identity();
        p_ProjectionMatrix->Perspective(Math::PMath::Deg2Rad(FOV), width / height, NEAR_PLANE, FAR_PLANE);
    }
}