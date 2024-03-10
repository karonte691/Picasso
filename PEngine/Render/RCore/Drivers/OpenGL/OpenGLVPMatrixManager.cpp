#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLVPMatrixManager.h>

#include <PEngine/Math/PMath.h>
#include <PEngine/Camera/Camera.h> //need this for viewMatrix

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    /**
     * @brief The field of view (FOV) for the projection matrix.
     */
    static const float FOV = 90.0f;

    /**
     * @brief The distance to the near clipping plane for the projection matrix.
     */
    static const float NEAR_PLANE = 0.1f;

    /**
     * @brief The distance to the far clipping plane for the projection matrix.
     */
    static const float FAR_PLANE = 1000.0f;

    /**
     * @brief Uniformly sets the view matrix in the shader program.
     *
     * @param shaderId The ID of the shader program.
     */
    void OpenGLVPMatrixManager::UniformViewMatrix(GLuint shaderId)
    {
        const Math::Mat4 *viewMatrix = Picasso::Engine::Camera::Camera::Instance->GetViewMatrix();

        glUniformMatrix4fv(glGetUniformLocation(shaderId, "ViewMatrix"), 1, GL_FALSE, &viewMatrix->m[0]);
    }

    /**
     * @brief Creates the projection matrix based on the given width and height.
     *
     * @param width The width of the viewport.
     * @param height The height of the viewport.
     */
    void OpenGLVPMatrixManager::CreateProjectionMatrix(float width, float height)
    {
        _initProjectionMatrix(width, height);
    }

    /**
     * @brief Uniformly sets the projection matrix in the shader program.
     *
     * @param shaderId The ID of the shader program.
     */
    void OpenGLVPMatrixManager::UniforProjectionMatrix(GLuint shaderId)
    {
        glUniformMatrix4fv(glGetUniformLocation(shaderId, "ProjectionMatrix"), 1, GL_FALSE, &p_ProjectionMatrix->m[0]);
    }

    /**
     * @brief Resets the projection matrix based on the given width and height.
     *
     * @param width The width of the viewport.
     * @param height The height of the viewport.
     */
    void OpenGLVPMatrixManager::ResetProjectionMatrix(float width, float height)
    {
        _initProjectionMatrix(width, height);
    }

    /**
     * @brief Uniformly sets both the view matrix and the projection matrix in the shader program.
     *
     * @param shaderId The ID of the shader program.
     */
    void OpenGLVPMatrixManager::UniformMatrices(GLuint shaderId)
    {
        UniformViewMatrix(shaderId);
        UniforProjectionMatrix(shaderId);
    }

    /**
     * @brief Initializes the projection matrix based on the given width and height.
     *
     * @param width The width of the viewport.
     * @param height The height of the viewport.
     */
    void OpenGLVPMatrixManager::_initProjectionMatrix(float width, float height)
    {
        p_ProjectionMatrix = Math::Mat4::Identity();
        p_ProjectionMatrix->Perspective(Math::PMath::Deg2Rad(FOV), width / height, NEAR_PLANE, FAR_PLANE);
    }
}