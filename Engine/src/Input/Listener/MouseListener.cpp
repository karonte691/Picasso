#include "MouseListener.h"

namespace Picasso::Engine::Input::Listener
{
    void MouseListener::ProcessButton(BUTTONS button, bool pressed, pInputState& inputState)
    {
        if(inputState.mouseCurrent.buttons[button] == pressed)
        {
            return;
        }
        
        inputState.mouseCurrent.buttons[button] = pressed;

        PEventData eData;
        eData.data.u16[0] = button;

        PicassoRegistry::Dispatch(pressed ? PEvent::BUTTON_PRESSED : PEvent::BUTTON_RELEASED, eData);   
    }

    void MouseListener::ProcessMouseMove(float x, float y, pInputState& inputState)
    {
        if(inputState.mouseCurrent.x == x && inputState.mouseCurrent.y == y)
        {
            return;
        }

        inputState.mouseCurrent.x = x;
        inputState.mouseCurrent.y = y;

        PEventData eData;
        eData.data.u16[0] = x;
        eData.data.u16[1] = y;

        PicassoRegistry::Dispatch(PEvent::MOUSE_MOVED, eData);
    }

    void MouseListener::GetMousePosition(float* x, float* y, pInputState& inputState)
    {
        if(x == nullptr){
            *x = 0;
            return;
        }

        if(y == nullptr){
            *y = 0;
            return;
        }

        *x = inputState.mouseCurrent.x;
        *y = inputState.mouseCurrent.y;
    }

    void MouseListener::GetPrevMousePosition(float* x, float* y, pInputState& inputState)
    {
        if(x == nullptr){
            *x = 0;
            return;
        }

        if(y == nullptr){
            *y = 0;
            return;
        }

        *x = inputState.mousePrev.x;
        *y = inputState.mousePrev.y;
    }

    void MouseListener::ProcessMouseWheels(int zDelta)
    {
        PEventData eData;
        eData.data.u8[0] = zDelta;

        PicassoRegistry::Dispatch(PEvent::MOUSE_WHEEL, eData);
    }

    bool MouseListener::IsButtonDown(BUTTONS button, pInputState& inputState)
    {
        return inputState.mouseCurrent.buttons[button] == true;
    }

    bool MouseListener::IsButtonUp(BUTTONS button, pInputState& inputState)
    {
        return inputState.mouseCurrent.buttons[button] == false;
    }

    bool MouseListener::WasButtonDown(BUTTONS button, pInputState& inputState)
    {
        return inputState.mousePrev.buttons[button] == true;
    }

    bool MouseListener::WasButtonUp(BUTTONS button, pInputState& inputState)
    {
        return inputState.mousePrev.buttons[button] == false;
    }
}