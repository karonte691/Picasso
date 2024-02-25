#include <PEngine/Controller/MovementController.h>

#include <PEngine/Logger/Logger.h>
#include <PEngine/Input/InputState.h>
#include <PEngine/EventSystem/PERegistry.h>

namespace Picasso::Engine::Controller
{
    bool MovementController::InitController()
    {
        m_Position = Math::Vector3::Zero();
        m_Rotation = Math::Vector3::Zero();

        PicassoRegistry::Subscribe(PEvent::CONTROLLER_MOVEMENT, [this](BaseEvent<PEvent> *&event)
                                   { this->_onMovement(event); });

        Picasso::Engine::Logger::Logger::Debug("MovementController initialized");
        return true;
    }

    void MovementController::_onMovement(BaseEvent<PEvent> *&event)
    {
        EventSystem::Events::PEventData eData = event->GetData();
        Input::InputDirection direction = static_cast<Input::InputDirection>(eData.data.u16[0]);

        switch (direction)
        {
        case Input::InputDirection::UP:
            m_Position.z -= 0.01f;
            break;
        case Input::InputDirection::DOWN:
            m_Position.z += 0.01f;
            break;
        case Input::InputDirection::LEFT:
            m_Position.x -= 0.01f;
            break;
        case Input::InputDirection::RIGHT:
            m_Position.x += 0.01f;
            break;
        case Input::InputDirection::BACKWARD:
            m_Rotation.y -= 1.0f;
            break;
        case Input::InputDirection::FORWARD:
            m_Rotation.y += 1.0f;
            break;
        default:
            // nothing to do, return
            return;
        }
        EventSystem::Events::PEventData eDataOut;

        // m_Position
        eDataOut.data.f32[0] = m_Position.x;
        eDataOut.data.f32[1] = m_Position.y;
        eDataOut.data.f32[2] = m_Position.z;
        eDataOut.data.f32[3] = m_Rotation.x;

        // m_Rotation
        eDataOut.data.f32[4] = m_Rotation.y;
        eDataOut.data.f32[5] = m_Rotation.z;

        PicassoRegistry::Dispatch(PEvent::CAMERA_UPDATE, eDataOut);
    }
} // namespace Picasso::Engine::Controller