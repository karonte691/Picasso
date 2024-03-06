/**
 * @file MovementController.cpp
 * @brief Implementation of the MovementController class.
 */

#include <PEngine/Controller/MovementController.h>

#include <PEngine/Logger/Logger.h>
#include <PEngine/EventSystem/PERegistry.h>
#include <string>
#include <PEngine/PBuild.h>

namespace Picasso::Engine::Controller
{
    /**
     * @brief Initializes the MovementController.
     * @return True if the initialization is successful, false otherwise.
     */
    bool MovementController::InitController()
    {
        // Initialize member variables
        m_Position = Math::Vector3::Zero();
        m_Rotation = Math::Vector3::Zero();
        m_Scale = Math::Vector3::One();
        m_IsPressed = false;
        m_CurrentDirection = Input::InputAction::NONE;

        // Subscribe to the CONTROLLER_MOVEMENT event
        PicassoRegistry::Subscribe(PEvent::CONTROLLER_MOVEMENT, [this](BaseEvent<PEvent> *&event)
                                   { this->_onMovement(event); });

        // Log initialization message
        Picasso::Engine::Logger::Logger::Debug("MovementController initialized");
        return true;
    }

    /**
     * @brief Updates the input state of the MovementController.
     * @param eData The event data containing the input state.
     */
    void MovementController::_UpdateInputState(const EventSystem::Events::PEventData &eData)
    {
        // Update current direction and pressed state
        m_CurrentDirection = static_cast<Input::InputAction>(eData.data.i[0]);
        m_IsPressed = static_cast<bool>(eData.data.i[1]);

#if PICASSO_DEBUG_ENABLE
        // Log input state update
        Picasso::Engine::Logger::Logger::Debug("MovementController: Input state updated to %s", _DebugPrintPosition(m_CurrentDirection).c_str());
#endif
    }

    /**
     * @brief Updates the MovementController.
     */
    void MovementController::Update()
    {
        if (!m_IsPressed)
        {
            // Reset current direction if not pressed
            m_CurrentDirection = Input::InputAction::NONE;
            return;
        }

        // Update position or rotation based on current direction
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
        case Input::InputAction::ROTATE_Y_AXIS_BACKWARD:
            m_Rotation.y -= 0.01f;
            break;
        case Input::InputAction::ROTATE_Y_AXIS_FORWARD:
            m_Rotation.y += 0.01f;
            break;
        case Input::InputAction::ROTATE_X_AXIS_FORWARD:
            m_Rotation.x -= 0.01f;
            break;
        case Input::InputAction::ROTATE_X_AXIS_BACKWARD:
            m_Rotation.x += 0.01f;
            break;
        default:
            return;
        }

        // Dispatch the update event
        _DispatchUpdate();
    }

    /**
     * @brief Dispatches the update event with the current position, rotation, and scale.
     */
    void MovementController::_DispatchUpdate()
    {
        EventSystem::Events::PEventData eDataOut;

        // Set event data with current position, rotation, and scale
        eDataOut.data.f[0] = m_Position.x;
        eDataOut.data.f[1] = m_Position.y;
        eDataOut.data.f[2] = m_Position.z;
        eDataOut.data.f[3] = m_Rotation.x;
        eDataOut.data.f[4] = m_Rotation.y;
        eDataOut.data.f[5] = m_Rotation.z;
        eDataOut.data.f[6] = m_Scale.x;
        eDataOut.data.f[7] = m_Scale.y;
        eDataOut.data.f[8] = m_Scale.z;

        // Dispatch the event
        PicassoRegistry::Dispatch(PEvent::CAMERA_UPDATE, eDataOut);
    }

    /**
     * @brief Handles the CONTROLLER_MOVEMENT event.
     * @param event The event containing the movement data.
     */
    void MovementController::_onMovement(BaseEvent<PEvent> *&event)
    {
        EventSystem::Events::PEventData eData = event->GetData();
        _UpdateInputState(eData);

        if (!m_IsPressed)
        {
            // Reset current direction if not pressed
            m_CurrentDirection = Input::InputAction::NONE;
        }
    }

#if PICASSO_DEBUG_ENABLE
    /**
     * @brief Returns a string representation of the input action for debugging purposes.
     * @param direction The input action.
     * @return The string representation of the input action.
     */
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
        case Input::InputAction::ROTATE_Y_AXIS_FORWARD:
            return "FORWARD";
        case Input::InputAction::ROTATE_Y_AXIS_BACKWARD:
            return "BACKWARD";
        case Input::InputAction::ROTATE_X_AXIS_FORWARD:
            return "SCALE_UP";
        case Input::InputAction::ROTATE_X_AXIS_BACKWARD:
            return "SCALE_DOWN";
        case Input::InputAction::NONE:
            return "NONE";
        default:
            return "UNKNOWN";
        }
    }
#endif

} // namespace Picasso::Engine::Controller