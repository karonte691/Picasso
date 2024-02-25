#include <PEngine/Input/InputListener.h>

#include <PEngine/Input/Maps/Keyboard.h>
#include <PEngine/Input/InputState.h>

namespace Picasso::Engine::Input
{
    void InputListener::Init()
    {
        PicassoRegistry::Subscribe(PEvent::KEY_PRESSED, [this](BaseEvent<PEvent> *&event)
                                   { this->_ProcessInput(event); });
        PicassoRegistry::Subscribe(PEvent::KEY_RELEASED, [this](BaseEvent<PEvent> *&event)
                                   { this->_ProcessInput(event); });
        PicassoRegistry::Subscribe(PEvent::BUTTON_PRESSED, [this](BaseEvent<PEvent> *&event)
                                   { this->_ProcessInput(event); });
        PicassoRegistry::Subscribe(PEvent::BUTTON_RELEASED, [this](BaseEvent<PEvent> *&event)
                                   { this->_ProcessInput(event); });
        PicassoRegistry::Subscribe(PEvent::MOUSE_MOVED, [this](BaseEvent<PEvent> *&event)
                                   { this->_ProcessInput(event); });
        PicassoRegistry::Subscribe(PEvent::MOUSE_WHEEL, [this](BaseEvent<PEvent> *&event)
                                   { this->_ProcessInput(event); });
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
            // Process mouse move
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

        // check if it is a movement
        if (!(key == P_KEY_W || key == P_KEY_UP || key == P_KEY_S || key == P_KEY_DOWN ||
              key == P_KEY_A || key == P_KEY_LEFT || key == P_KEY_D || key == P_KEY_RIGHT ||
              key == P_KEY_Q || key == P_KEY_E))
        {
            return;
        }

        InputDirection direction;

        // determine the direction based on the key
        switch (key)
        {
        case P_KEY_W:
        case P_KEY_UP:
            direction = InputDirection::UP;
            break;
        case P_KEY_S:
        case P_KEY_DOWN:
            direction = InputDirection::DOWN;
            break;
        case P_KEY_A:
        case P_KEY_LEFT:
            direction = InputDirection::LEFT;
            break;
        case P_KEY_D:
        case P_KEY_RIGHT:
            direction = InputDirection::RIGHT;
            break;
        case P_KEY_Q:
            direction = InputDirection::FORWARD;
            break;
        case P_KEY_E:
            direction = InputDirection::BACKWARD;
            break;
        default:
            return;
        }

        if (pressed)
        {
            // Dispatch the controller movement event with the determined direction
            PEventData movementData;
            movementData.data.u16[0] = static_cast<u_int16_t>(direction);
            PicassoRegistry::Dispatch(PEvent::CONTROLLER_MOVEMENT, movementData);
        }
    }
} // namespace Picasso::Engine::Input::Listener
