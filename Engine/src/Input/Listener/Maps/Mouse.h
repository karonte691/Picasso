#pragma once

#ifndef MOUSE_H
#define MOUSE_H

namespace Picasso::Engine::Input
{
    enum BUTTONS
    {
        #define P_MOUSE_BUTTON_1         0
        #define P_MOUSE_BUTTON_2         1
        #define P_MOUSE_BUTTON_3         2
        #define P_MOUSE_BUTTON_4         3
        #define P_MOUSE_BUTTON_5         4
        #define P_MOUSE_BUTTON_6         5
        #define P_MOUSE_BUTTON_7         6
        #define P_MOUSE_BUTTON_8         7
        #define P_MOUSE_BUTTON_LAST      P_MOUSE_BUTTON_8
        #define P_MOUSE_BUTTON_LEFT      P_MOUSE_BUTTON_1
        #define P_MOUSE_BUTTON_RIGHT     P_MOUSE_BUTTON_2
        #define P_MOUSE_BUTTON_MIDDLE    P_MOUSE_BUTTON_3
    };

}

#endif