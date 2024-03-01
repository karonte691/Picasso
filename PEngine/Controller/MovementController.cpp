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
        m_Scale = Math::Vector3::One();
        m_IsPressed = false;
        m_CurrentDirection = Input::InputAction::NONE;

        PicassoRegistry::Subscribe(PEvent::CONTROLLER_MOVEMENT, [this](BaseEvent<PEvent> *&event)
                                   { this->_onMovement(event); });

        Picasso::Engine::Logger::Logger::Debug("MovementController initialized");
        return true;
    }

    void MovementController::_UpdateInputState(const EventSystem::Events::PEventData &eData)
    {
        m_CurrentDirection = static_cast<Input::InputAction>(eData.data.i[0]);
        m_IsPressed = static_cast<bool>(eData.data.i[1]);

#if PICASSO_DEBUG_ENABLE
        Picasso::Engine::Logger::Logger::Debug("MovementController: Input state updated to %s", _DebugPrintPosition(m_CurrentDirection).c_str());
#endif
    }

    void MovementController::Update()
    {
        if (!m_IsPressed)
        {
            m_CurrentDirection = Input::InputAction::NONE;
            return;
        }

        Math::Vector3 *sVec = new Math::Vector3{0.1f, 0.1f, 0.1f};

        switch (m_CurrentDirection)
        {
        case Input::InputAction::UP:
            m_Position.z -= 0.01f;
            break;
        case Input::InputAction::DOWN:
            m_Position.z += 0.01f;
            break;
        case Input::InputAction::LEFT:
            m_Position.x -= 0.01f;
            break;
        case Input::InputAction::RIGHT:
            m_Position.x += 0.01f;
            break;
        case Input::InputAction::BACKWARD:
            m_Rotation.y -= 1.0f;
            break;
        case Input::InputAction::FORWARD:
            m_Rotation.y += 1.0f;
            break;
        case Input::InputAction::SCALE_UP:
            m_Scale.Add(sVec);
            break;
        case Input::InputAction::SCALE_DOWN:
            m_Scale.Sub(sVec);
            break;
        default:
            return;
        }

        delete sVec;

        _DispatchUpdate();
    }

    void MovementController::_DispatchUpdate()
    {
        EventSystem::Events::PEventData eDataOut;

        eDataOut.data.f[0] = m_Position.x;
        eDataOut.data.f[1] = m_Position.y;
        eDataOut.data.f[2] = m_Position.z;
        eDataOut.data.f[3] = m_Rotation.x;
        eDataOut.data.f[4] = m_Rotation.y;
        eDataOut.data.f[5] = m_Rotation.z;
        eDataOut.data.f[6] = m_Scale.x;
        eDataOut.data.f[7] = m_Scale.y;
        eDataOut.data.f[8] = m_Scale.z;

        PicassoRegistry::Dispatch(PEvent::CAMERA_UPDATE, eDataOut);
    }

    void MovementController::_onMovement(BaseEvent<PEvent> *&event)
    {
        EventSystem::Events::PEventData eData = event->GetData();
        _UpdateInputState(eData);

        if (!m_IsPressed)
        {
            m_CurrentDirection = Input::InputAction::NONE;
        }
    }

#if PICASSO_DEBUG_ENABLE
    std::string MovementController::_DebugPrintPosition(Input::InputAction direction)
    {
        switch (direction)
        {
        case Input::InputAction::UP:
            return "UP";
        case Input::InputAction::DOWN:
            return "DOWN";
        case Input::InputAction::LEFT:
            return "LEFT";
        case Input::InputAction::RIGHT:
            return "RIGHT";
        case Input::InputAction::FORWARD:
            return "FORWARD";
        case Input::InputAction::BACKWARD:
            return "BACKWARD";
        case Input::InputAction::SCALE_UP:
            return "SCALE_UP";
        case Input::InputAction::SCALE_DOWN:
            return "SCALE_DOWN";
        case Input::InputAction::NONE:
            return "NONE";
        default:
            return "UNKNOWN";
        }
    }
#endif

} // namespace Picasso::Engine::Controller