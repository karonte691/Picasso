#include <PEngine/Controller/CameraController.h>

namespace Picasso::Engine::Controller
{
    /**
     * @brief Initializes the camera controller.
     *
     * This function subscribes to the CAMERA_UPDATE event and sets the callback function to _onCameraUpdate.
     *
     * @return true if the controller is successfully initialized, false otherwise.
     */
    bool CameraController::InitController()
    {
        PicassoRegistry::Subscribe(PEvent::CAMERA_UPDATE, [this](BaseEvent<PEvent> *&event)
                                   { this->_onCameraUpdate(event); });
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

    /**
     * @brief Handles the camera update event.
     *
     * This function is a bridge to update the position, rotation, and scale of the matrices in the renderer.
     * It logs a debug message and dispatches the RENDERER_UPDATE event with the event data.
     *
     * @param event The camera update event.
     */
    void CameraController::_onCameraUpdate(BaseEvent<PEvent> *&event)
    {
        EventSystem::Events::PEventData eData = event->GetData();

        Picasso::Engine::Logger::Logger::Debug("CameraController: Updating camera position, rotation, and scale");

        PicassoRegistry::Dispatch(PEvent::RENDERER_UPDATE, eData);
    }
}