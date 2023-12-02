#include <PEngine/Input/Listener/KeyboardListener.h>

namespace Picasso::Engine::Input::Listener
{
    void KeyboardListener::ProcessKey(KEYS key, bool pressed, pInputState& inputState)
    {
        if(inputState.keyboardCurrent.key[key] == pressed)
        {
            return;
        }
        
        inputState.keyboardCurrent.key[key] = pressed;

        PEventData eData;
        eData.data.u16[0] = key;

        PicassoRegistry::Dispatch(pressed ? PEvent::KEY_PRESSED : PEvent::KEY_RELEASED, eData);   
    }

    bool KeyboardListener::IsKeyDown(KEYS key, pInputState& inputState)
    {
        return inputState.keyboardCurrent.key[key] == true;
    }

    bool KeyboardListener::IsKeyUp(KEYS key, pInputState& inputState)
    {
        return inputState.keyboardCurrent.key[key] == false;
    }

    bool KeyboardListener::WasKeyDown(KEYS key, pInputState& inputState)
    {
        return inputState.keyboardPrev.key[key] == true;
    }

    bool KeyboardListener::WasKeyUp(KEYS key, pInputState& inputState)
    {
        return inputState.keyboardPrev.key[key] == false;
    }
}