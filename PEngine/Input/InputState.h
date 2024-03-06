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
        ROTATE_Y_AXIS_FORWARD,
        ROTATE_Y_AXIS_BACKWARD,
        ROTATE_X_AXIS_FORWARD,
        ROTATE_X_AXIS_BACKWARD,
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