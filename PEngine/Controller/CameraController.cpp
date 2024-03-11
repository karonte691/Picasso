#include <PEngine/Controller/CameraController.h>

#include <PEngine/Camera/Camera.h>

namespace Picasso::Engine::Controller
{
    using Picasso::Engine::Camera::Camera;

    /**
     * @brief Initializes the camera controller.
     *
     * This function subscribes to the CAMERA_UPDATE event and sets the callback function to _onCameraUpdate.
     *
     * @return true if the controller is successfully initialized, false otherwise.
     */
    bool CameraController::InitController()
    {
        Picasso::Engine::Camera::Camera::Instance = new Camera(Math::Vector3{0.0f, 0.0f, 1.0f}, Math::Vector3{0.0f, 1.0f, 0.0f});

        PicassoRegistry::Subscribe(this, PEvent::CAMERA_UPDATE_VIEW, [this](BaseEvent<PEvent> *&event)
                                   { this->_OnCameraUpdateView(event); });
        PicassoRegistry::Subscribe(this, PEvent::CAMERA_UPDATE_POSITION, [this](BaseEvent<PEvent> *&event)
                                   { this->_OnCameraUpdatePosition(event); });

        return true;
    }

    /**
     * @brief Updates the camera controller.
     *
     * This function is currently empty as there is nothing to update in the camera controller.
     */
    void CameraController::Update()
    {
        // nothing to do here
    }

    void CameraController::Destroy()
    {
        Picasso::Engine::EventSystem::PicassoRegistry::Unsubscribe(this, PEvent::CAMERA_UPDATE_POSITION);
        Picasso::Engine::EventSystem::PicassoRegistry::Unsubscribe(this, PEvent::CAMERA_UPDATE_VIEW);

        delete Picasso::Engine::Camera::Camera::Instance;
    }

    void CameraController::_OnCameraUpdateView(BaseEvent<PEvent> *&event)
    {
        EventSystem::Events::PEventData eData = event->GetData();

        unsigned int x = eData.data.u16[0];
        unsigned int y = eData.data.u16[1];

        if (m_PrevX == x && m_PrevY == y)
        {
            // do nothing
            return;
        }

        m_PrevX = x;
        m_PrevY = y;

        Picasso::Engine::Camera::Camera::Instance->UpdateCameraView(x, y);

        PicassoRegistry::Dispatch(PEvent::RENDERER_UPDATE_CAMERA_VIEW);
    }

    void CameraController::_OnCameraUpdatePosition(BaseEvent<PEvent> *&event)
    {
        EventSystem::Events::PEventData eData = event->GetData();

        Input::InputAction direction = static_cast<Input::InputAction>(eData.data.i[0]);

        Picasso::Engine::Camera::Camera::Instance->UpdateCameraPosition(direction);

        PicassoRegistry::Dispatch(PEvent::RENDERER_UPDATE_CAMERA_POSITION);
    }
}