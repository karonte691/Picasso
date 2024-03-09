#include <PEngine/Input/InputListener.h>

#include <PEngine/Input/Maps/Keyboard.h>
#include <PEngine/Input/InputState.h>
#include <PEngine/Logger/Logger.h>

namespace Picasso::Engine::Input
{
    void InputListener::Init()
    {
        PicassoRegistry::Subscribe(this, PEvent::KEY_PRESSED, [this](BaseEvent<PEvent> *&event)
                                   { this->_ProcessInput(event); });
        PicassoRegistry::Subscribe(this, PEvent::KEY_RELEASED, [this](BaseEvent<PEvent> *&event)
                                   { this->_ProcessInput(event); });
        PicassoRegistry::Subscribe(this, PEvent::BUTTON_PRESSED, [this](BaseEvent<PEvent> *&event)
                                   { this->_ProcessInput(event); });
        PicassoRegistry::Subscribe(this, PEvent::BUTTON_RELEASED, [this](BaseEvent<PEvent> *&event)
                                   { this->_ProcessInput(event); });
        PicassoRegistry::Subscribe(this, PEvent::MOUSE_MOVED, [this](BaseEvent<PEvent> *&event)
                                   { this->_ProcessInput(event); });
        PicassoRegistry::Subscribe(this, PEvent::MOUSE_WHEEL, [this](BaseEvent<PEvent> *&event)
                                   { this->_ProcessInput(event); });
    }

    void InputListener::Destroy()
    {
        PicassoRegistry::Unsubscribe(this, PEvent::KEY_PRESSED);
        PicassoRegistry::Unsubscribe(this, PEvent::KEY_RELEASED);
        PicassoRegistry::Unsubscribe(this, PEvent::BUTTON_PRESSED);
        PicassoRegistry::Unsubscribe(this, PEvent::BUTTON_RELEASED);
        PicassoRegistry::Unsubscribe(this, PEvent::MOUSE_MOVED);
        PicassoRegistry::Unsubscribe(this, PEvent::MOUSE_WHEEL);
    }

    void InputListener::_ProcessInput(BaseEvent<PEvent> *&event)
    {
        // Process input
        PEventData eData = event->GetData();

        switch (event->type())
        {
        case PEvent::KEY_PRESSED:
            _ProcessKeyInput(eData, true);
            break;
        case PEvent::KEY_RELEASED:
            _ProcessKeyInput(eData, false);
            break;
        case PEvent::BUTTON_PRESSED:
            // Process button press
            break;
        case PEvent::BUTTON_RELEASED:
            // Process button release
            break;
        case PEvent::MOUSE_MOVED:
            _ProcessMouseInput(eData);
            break;
        case PEvent::MOUSE_WHEEL:
            // Process mouse wheel
            break;
        default:
            break;
        }
    }

    void InputListener::_ProcessKeyInput(PEventData &eData, bool pressed)
    {
        u_int16_t key = eData.data.u16[0];

        InputAction direction = InputAction::NONE;

        // determine the direction based on the key
        switch (key)
        {
        case P_KEY_W:
        case P_KEY_UP:
            direction = InputAction::UP;
            break;
        case P_KEY_S:
        case P_KEY_DOWN:
            direction = InputAction::DOWN;
            break;
        case P_KEY_A:
        case P_KEY_LEFT:
            direction = InputAction::LEFT;
            break;
        case P_KEY_D:
        case P_KEY_RIGHT:
            direction = InputAction::RIGHT;
            break;
            /*
        case P_KEY_Q:
            direction = InputAction::ROTATE_Y_AXIS_FORWARD;
            break;
        case P_KEY_E:
            direction = InputAction::ROTATE_Y_AXIS_BACKWARD;
            break;
        case P_KEY_Z:
            direction = InputAction::ROTATE_X_AXIS_FORWARD;
            break;
        case P_KEY_C:
            direction = InputAction::ROTATE_X_AXIS_BACKWARD;
            break;
            */
        default:
            return;
        }

        if (direction == InputAction::NONE)
        {
            return;
        }

        PEventData movementData;

        movementData.data.i[0] = static_cast<int>(direction); // Assign the int value of direction to movementData.data.i[0]
        movementData.data.i[1] = static_cast<int>(pressed);   // Assign the int value of pressed to movementData.data.i[1]

        PicassoRegistry::Dispatch(PEvent::CONTROLLER_MOVEMENT, movementData);
        PicassoRegistry::Dispatch(PEvent::CAMERA_UPDATE_POSITION, movementData);
    }

    void InputListener::_ProcessMouseInput(PEventData &eData)
    {
        // here we just need to pass x and y to the CameraController
        PicassoRegistry::Dispatch(PEvent::CAMERA_UPDATE_VIEW, eData);
    }
} // namespace Picasso::Engine::Input::Listener
