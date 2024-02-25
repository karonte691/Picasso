#include <PEngine/Controller/MovementController.h>

#include <PEngine/Logger/Logger.h>
#include <PEngine/Input/InputState.h>
#include <PEngine/Math/Vector3.h>
#include <PEngine/EventSystem/PERegistry.h>

namespace Picasso::Engine::Controller
{
    bool MovementController::InitController()
    {
        PicassoRegistry::Subscribe(PEvent::CONTROLLER_MOVEMENT, [this](BaseEvent<PEvent> *&event)
                                   { this->_onMovement(event); });

        Picasso::Engine::Logger::Logger::Debug("MovementController initialized");
        return true;
    }

    void MovementController::_onMovement(BaseEvent<PEvent> *&event)
    {
        EventSystem::Events::PEventData eData = event->GetData();
        Input::InputDirection direction = static_cast<Input::InputDirection>(eData.data.u16[0]);

        Math::Vector3 position = Math::Vector3::Zero();
        Math::Vector3 rotation = Math::Vector3::Zero();

        switch (direction)
        {
        case Input::InputDirection::UP:
            position.z -= 0.01f;
            break;
        case Input::InputDirection::DOWN:
            position.z += 0.01f;
            break;
        case Input::InputDirection::LEFT:
            position.x -= 0.01f;
            break;
        case Input::InputDirection::RIGHT:
            position.x += 0.01f;
            break;
        case Input::InputDirection::BACKWARD:
            rotation.y -= 1.0f;
            break;
        case Input::InputDirection::FORWARD:
            rotation.y += 1.0f;
            break;
        default:
            // nothing to do, return
            return;
        }

        Picasso::Engine::Logger::Logger::Debug("MovementController: Moving in direction: %s", std::to_string(static_cast<int>(direction)));

        EventSystem::Events::PEventData eDataOut;

        // position
        eDataOut.data.f32[0] = position.x;
        eDataOut.data.f32[1] = position.y;
        eDataOut.data.f32[2] = position.z;
        eDataOut.data.f32[3] = rotation.x;

        // rotation
        eDataOut.data.f32[4] = rotation.y;
        eDataOut.data.f32[5] = rotation.z;

        PicassoRegistry::Dispatch(PEvent::CAMERA_UPDATE, eDataOut);
    }
} // namespace Picasso::Engine::Controller