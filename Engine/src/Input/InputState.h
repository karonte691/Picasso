#pragma once

#ifndef INPUT_STATE_H
#define INPUT_STATE_H

namespace Picasso::Engine::Input
{
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