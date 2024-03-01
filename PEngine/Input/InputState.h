#pragma once

#ifndef INPUT_STATE_H
#define INPUT_STATE_H

#include <string>

namespace Picasso::Engine::Input
{
    enum class InputAction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        FORWARD,
        BACKWARD,
        SCALE_UP,
        SCALE_DOWN,
        NONE
    };

    struct kState
    {
        bool key[256];
    };

    struct mState
    {
        float x;
        float y;
        bool buttons[12];
    };

    struct pInputState
    {
        kState keyboardCurrent;
        kState keyboardPrev;
        mState mouseCurrent;
        mState mousePrev;
    };
}

#endif