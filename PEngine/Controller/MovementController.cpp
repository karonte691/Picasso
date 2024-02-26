#include <PEngine/Controller/MovementController.h>

#include <PEngine/Logger/Logger.h>
#include <PEngine/EventSystem/PERegistry.h>
#include <string>
#include <PEngine/PBuild.h>

namespace Picasso::Engine::Controller
{
    bool MovementController::InitController()
    {
        m_Position = Math::Vector3::Zero();
        m_Rotation = Math::Vector3::Zero();
        m_IsPressed = false;
        m_CurrentDirection = Input::InputDirection::NONE;

        PicassoRegistry::Subscribe(PEvent::CONTROLLER_MOVEMENT, [this](BaseEvent<PEvent> *&event)
                                   { this->_onMovement(event); });

        Picasso::Engine::Logger::Logger::Debug("MovementController initialized");
        return true;
    }

    void MovementController::_UpdateInputState(const EventSystem::Events::PEventData &eData)
    {
        m_CurrentDirection = static_cast<Input::InputDirection>(eData.data.i[0]);
        m_IsPressed = static_cast<bool>(eData.data.i[1]);

#if PICASSO_DEBUG_ENABLE
        Picasso::Engine::Logger::Logger::Debug("MovementController: Input state updated to %s", _DebugPrintPosition(m_CurrentDirection).c_str());
#endif
    }

    void MovementController::Update()
    {
        if (!m_IsPressed)
        {
            m_CurrentDirection = Input::InputDirection::NONE;
            return;
        }

        switch (m_CurrentDirection)
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
            // If direction is not recognized, do nothing
            return;
        }

        _DispatchUpdate();
    }

    void MovementController::_DispatchUpdate()
    {
        EventSystem::Events::PEventData eDataOut;

        eDataOut.data.f32[0] = m_Position.x;
        eDataOut.data.f32[1] = m_Position.y;
        eDataOut.data.f32[2] = m_Position.z;
        eDataOut.data.f32[3] = m_Rotation.x;
        eDataOut.data.f32[4] = m_Rotation.y;
        eDataOut.data.f32[5] = m_Rotation.z;

        PicassoRegistry::Dispatch(PEvent::CAMERA_UPDATE, eDataOut);
    }

    void MovementController::_onMovement(BaseEvent<PEvent> *&event)
    {
        EventSystem::Events::PEventData eData = event->GetData();
        _UpdateInputState(eData);

        if (!m_IsPressed)
        {
            m_CurrentDirection = Input::InputDirection::NONE;
        }
    }

#if PICASSO_DEBUG_ENABLE
    std::string MovementController::_DebugPrintPosition(Input::InputDirection direction)
    {
        switch (direction)
        {
        case Input::InputDirection::UP:
            return "UP";
        case Input::InputDirection::DOWN:
            return "DOWN";
        case Input::InputDirection::LEFT:
            return "LEFT";
        case Input::InputDirection::RIGHT:
            return "RIGHT";
        case Input::InputDirection::FORWARD:
            return "FORWARD";
        case Input::InputDirection::BACKWARD:
            return "BACKWARD";
        case Input::InputDirection::NONE:
            return "NONE";
        default:
            return "UNKNOWN";
        }
    }
#endif

} // namespace Picasso::Engine::Controller