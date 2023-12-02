#include <PEngine/Input/Translator/MouseCodeTranslator.h>

#include <xcb/xproto.h>

namespace Picasso::Engine::Input::Translators
{
    BUTTONS MouseCodeTranslator::TranslateButton(uint8_t buttonCode)
    {
        BUTTONS btn = P_MOUSE_BUTTON_UNKW;

        switch(buttonCode)
        {
            case XCB_BUTTON_INDEX_1:
                btn = P_MOUSE_BUTTON_LEFT;
                break;
            case XCB_BUTTON_INDEX_3:
                btn = P_MOUSE_BUTTON_RIGHT;
                break;
            default:
                break;
        }

        return btn;
    }
}