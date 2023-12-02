#pragma once

#ifndef KEY_CODE_TRANSLATOR_H
#define KEY_CODE_TRANSLATOR_H

#include <cstdint>

#include <PEngine/Input/Maps/Keyboard.h>

namespace Picasso::Engine::Input::Translators
{
    class KeyCodeTranslator
    {
        public:
            KEYS TranslateKey(uint32_t keyCode);
    };
}
#endif