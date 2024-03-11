#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <PEngine/Math/Vector3.h>
#include <PEngine/Math/Mat4.h>
#include <PEngine/Input/InputState.h>

#include <memory>

namespace Picasso::Engine::Camera
{
    class Camera
    {
    public:
        Camera(Math::Vector3 position, Math::Vector3 up);

        static Camera *Instance;

        Math::Mat4 *GetViewMatrix();
        inline const Math::Vector3 *GetPosition() const { return &m_Position; }

        void UpdateVectors();
        void UpdateCameraPosition(Input::InputAction inputAction);
        void UpdateCameraView(unsigned int x, unsigned int y);

    private:
        Math::Vector3 m_Position;
        Math::Vector3 m_Front;
        Math::Vector3 m_Right;
        Math::Vector3 m_Up;
        Math::Vector3 m_WorldUp;
        std::unique_ptr<Math::Mat4> p_ViewMatrix;
        float m_Pitch;
        float m_Yaw;
        float m_Roll;
        float m_Speed;
        float m_Sensitivity;
    };
}

#endif // P_CAMERA_H