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

        PicassoRegistry::Dispatch(pressed ? PEvent::BUTTON_PRESSED : PEvent::BUTTON_RELEASED);   
    }
}