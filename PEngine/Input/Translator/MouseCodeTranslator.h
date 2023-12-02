#pragma once

#ifndef MOUSE_CODE_TRANSLATOR_H
#define MOUSE_CODE_TRANSLATOR_H

#include <cstdint>
#include <PEngine/Input/Maps/Mouse.h>

namespace Picasso::Engine::Input::Translators
{
    class MouseCodeTranslator
    {
        public:
            BUTTONS TranslateButton(uint8_t buttonCode);
    };
}
#endif