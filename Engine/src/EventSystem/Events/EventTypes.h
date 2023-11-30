#pragma once

#ifndef EVENT_TYPES_H
#define EVENT_TYPES_H

namespace Picasso::Engine::EventSystem::Events
{
    enum class PEvent
    {
        APPLICATION_QUIT,
        RESIZED,
        KEY_PRESSED,
        KEY_RELEASED,
        BUTTON_PRESSED,
        BUTTON_RELEASED,
        MOUSE_MOVED,
        MOUSE_WHEEL
    };
}

#endif