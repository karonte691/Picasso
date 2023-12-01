#pragma once

#ifndef MOUSE_H
#define MOUSE_H

namespace Picasso::Engine::Input
{
    enum BUTTONS
    {
        P_MOUSE_BUTTON_1      =   0,
        P_MOUSE_BUTTON_2      =   1,
        P_MOUSE_BUTTON_3      =   2,
        P_MOUSE_BUTTON_4      =   3,
        P_MOUSE_BUTTON_5      =   4,
        P_MOUSE_BUTTON_6      =   5,
        P_MOUSE_BUTTON_7      =   6,
        P_MOUSE_BUTTON_8      =   7,
        P_MOUSE_BUTTON_LAST   =   P_MOUSE_BUTTON_8,
        P_MOUSE_BUTTON_LEFT   =   P_MOUSE_BUTTON_1,
        P_MOUSE_BUTTON_RIGHT  =   P_MOUSE_BUTTON_2,

        P_MOUSE_BUTTON_UNKW   =   -1
    };

}

#endif