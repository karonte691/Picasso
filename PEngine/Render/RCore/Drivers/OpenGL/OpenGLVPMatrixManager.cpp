#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLVPMatrixManager.h>

#include <PEngine/Math/PMath.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    static const float FOV = 90.0f;
    static const float NEAR_PLANE = 0.1f;
    static const float FAR_PLANE = 1000.0f;

    void OpenGLVPMatrixManager::CreateViewMatrix()
    {
        m_CamPosition = Math::Vector3(0.0f, 0.0f, 1.0f); // (0.0f, 0.0f, 3.0f
        m_WorlUp = Math::Vector3(0.0f, 1.0f, 0.0f);
        m_CamFront = Math::Vector3(0.0f, 0.0f, -1.0f);

        p_ViewMatrix = Math::Mat4::Identity();
        p_ViewMatrix->LookAt(m_CamPosition, m_CamPosition.Add(&m_CamFront), m_WorlUp);
    }

    void OpenGLVPMatrixManager::UniformViewMatrix(GLuint shaderId)
    {
        glUniformMatrix4fv(glGetUniformLocation(shaderId, "ViewMatrix"), 1, GL_FALSE, &p_ViewMatrix->m[0]);
    }

    void OpenGLVPMatrixManager::CreateProjectionMatrix(float width, float height)
    {
        _initProjectionMatrix(width, height);
    }

    void OpenGLVPMatrixManager::UniforProjectionMatrix(GLuint shaderId)
    {
        glUniformMatrix4fv(glGetUniformLocation(shaderId, "ProjectionMatrix"), 1, GL_FALSE, &p_ProjectionMatrix->m[0]);
    }

    void OpenGLVPMatrixManager::ResetProjectionMatrix(float width, float height)
    {
        _initProjectionMatrix(width, height);
    }

    void OpenGLVPMatrixManager::UniformMatrices(GLuint shaderId)
    {
        UniformViewMatrix(shaderId);
        UniforProjectionMatrix(shaderId);
    }

    void OpenGLVPMatrixManager::UniformCameraPosition(unsigned int shaderProgram)
    {
        int camPosLocation = glGetUniformLocation(shaderProgram, "cameraPosition");
        glUniform3fv(camPosLocation, 1, &m_CamPosition.x);
    }

    void OpenGLVPMatrixManager::_initProjectionMatrix(float width, float height)
    {
        p_ProjectionMatrix = Math::Mat4::Identity();
        p_ProjectionMatrix->Perspective(Math::PMath::Deg2Rad(FOV), width / height, NEAR_PLANE, FAR_PLANE);
    }
}