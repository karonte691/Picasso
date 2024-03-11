#include <PEngine/Camera/Camera.h>

#include <PEngine/Math/PMath.h>
#include <cmath>

namespace Picasso::Engine::Camera
{
    static const float CAMERA_SPEED = 3.0f;
    static const float CAMERA_SENSITIVITY = 5.0f;
    static const float CAMERA_YAW = -90.0f;
    static const float CAMERA_PITCH = 0.0f;
    static const float CAMERA_ROLL = 0.0f;

    Camera *Camera::Instance = nullptr;

    Camera::Camera(Math::Vector3 position, Math::Vector3 up)
    {
        p_ViewMatrix = Math::Mat4::Identity();
        m_Speed = CAMERA_SPEED;
        m_Sensitivity = CAMERA_SENSITIVITY;
        m_Pitch = CAMERA_PITCH;
        m_Yaw = CAMERA_YAW;
        m_Roll = CAMERA_ROLL;

        m_WorldUp = up;
        m_Up = up;
        m_Position = position;
        m_Right = {0.0f, 0.0f, 0.0f};
        m_Front = {0.0f, 0.0f, 0.0f};
    }

    Math::Mat4 *Camera::GetViewMatrix()
    {
        UpdateVectors();

        m_Position.Add(&m_Front);
        p_ViewMatrix->LookAt(m_Position, m_Position, m_Up);

        return p_ViewMatrix.get();
    }

    void Camera::UpdateVectors()
    {
        m_Front.x = std::cos(Math::PMath::Deg2Rad(m_Yaw)) * std::cos(Math::PMath::Deg2Rad(m_Pitch));
        m_Front.y = std::sin(Math::PMath::Deg2Rad(m_Pitch));
        m_Front.z = std::sin(Math::PMath::Deg2Rad(m_Yaw)) * cos(Math::PMath::Deg2Rad(m_Pitch));

        m_Front.Normalize();

        m_Right = m_Front.GetNormalizedCopy();
        m_Right.Cross(&m_WorldUp).Normalize();

        m_Up = m_Right.GetNormalizedCopy();
        m_Up.Cross(&m_Front).Normalize();
    }

    void Camera::UpdateCameraView(unsigned int x, unsigned int y)
    {
        m_Yaw += static_cast<float>(x) * m_Sensitivity;
        m_Pitch += static_cast<float>(y) * m_Sensitivity;

        if (m_Pitch > 89.0f)
        {
            m_Pitch = 89.0f;
        }
        else
        {
            if (m_Pitch < -89.0f)
            {
                m_Pitch = -89.0f;
            }
        }

        if (m_Yaw > 360.0f || m_Yaw < -360.0f)
        {
            m_Yaw = 0.0f;
        }
    }

    void Camera::UpdateCameraPosition(Input::InputAction inputAction)
    {
        switch (inputAction)
        {
        case Input::InputAction::UP:
            m_Front.Multiply(m_Speed);
            m_Position = m_Position.Add(&m_Front);
            break;
        case Input::InputAction::DOWN:
            m_Front.Multiply(m_Speed);
            m_Position = m_Position.Sub(&m_Front);
            break;
        case Input::InputAction::LEFT:
            m_Right.Multiply(m_Speed);
            m_Position = m_Position.Sub(&m_Right);
            break;
        case Input::InputAction::RIGHT:
            m_Right.Multiply(m_Speed);
            m_Position = m_Position.Add(&m_Right);
            break;
        default:
            break;
        }
    }
} // namespace Picasso::Engine::Render::Core::Camera