#pragma once

#ifndef EVENT_TYPES_H
#define EVENT_TYPES_H

#include <cstdint>

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
        MOUSE_WHEEL,

        PLATFORM_EXPOSE
    };

    struct PEventData
    {
        union
        {
            int64_t i64[2];
            u_int64_t u64[2];
            _Float64 f64[2];

            int32_t i32[4];
            u_int32_t u32[4];
            _Float32 f32[4];

            int16_t i16[8];
            u_int16_t u16[8];

            int8_t i8[16];
            u_int8_t u8[16];

            char c[16];
        } data;
    };
}

#endif