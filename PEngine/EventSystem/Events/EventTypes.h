#pragma once

#ifndef EVENT_TYPES_H
#define EVENT_TYPES_H

#include <cstdint>
#include <string>
namespace Picasso::Engine::EventSystem::Events
{
    enum class PEvent
    {
        APPLICATION_QUIT,
        RESIZED,
        PLATFORM_EXPOSE,
        CAMERA_UPDATE_VIEW,
        CAMERA_UPDATE_POSITION,
        RENDERER_UPDATE,

        // keyboard
        KEY_PRESSED,
        KEY_RELEASED,
        BUTTON_PRESSED,
        BUTTON_RELEASED,

        // mouse
        MOUSE_MOVED,
        MOUSE_WHEEL,

        // controller
        CONTROLLER_MOVEMENT,
        CONTROLLER_SCALE,

    };

    struct PEventData
    {
        union
        {
            u_int16_t u16[16];
            u_int8_t u8[16];
            char c[16];
            float f[16]; // Modify this line to store six floats
            int i[16];
            bool b[16];
        } data;
    };
}

#endif