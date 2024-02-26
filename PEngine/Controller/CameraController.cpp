#include <PEngine/Controller/CameraController.h>

namespace Picasso::Engine::Controller
{
    bool CameraController::InitController()
    {
        PicassoRegistry::Subscribe(PEvent::CAMERA_UPDATE, [this](BaseEvent<PEvent> *&event)
                                   { this->_onCameraUpdate(event); });
        return true;
    }

    void CameraController::Update()
    {
        // nothing to do here
    }

    void CameraController::_onCameraUpdate(BaseEvent<PEvent> *&event)
    {
        // for now this is only a bridge to update the position and rotation of
        //  the matrices in the renderer
        EventSystem::Events::PEventData eData = event->GetData();

        Picasso::Engine::Logger::Logger::Debug("CameraController: Updating camera position and rotation");

        PicassoRegistry::Dispatch(PEvent::RENDERER_UPDATE, eData);
    }
}