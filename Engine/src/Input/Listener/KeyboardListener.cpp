#include "KeyboardListener.h"

namespace Picasso::Engine::Input::Listener
{
    
    void KeyboardListener::ProcessKey(KEYS key, bool pressed, pInputState& inputState)
    {
        if(inputState.keyboardCurrent.key[key] == pressed)
        {
            return;
        }
        
        inputState.keyboardCurrent.key[key] = pressed;

        PicassoRegistry::Dispatch(pressed ? PEvent::KEY_PRESSED : PEvent::KEY_RELEASED);   
    }
}