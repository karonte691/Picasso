#pragma once

#ifndef KEYBOARD_H
#define KEYBOARD_H

namespace Picasso::Engine::Input
{
    enum KEYS
    {
        //from P3.h
        /* Printable keys */
        P_KEY_UNKNOWN       =      0,
        P_KEY_SPACE         =     32,
        P_KEY_APOSTROPHE    =     39,
        P_KEY_COMMA         =     44,
        P_KEY_MINUS         =     45,
        P_KEY_PERIOD        =     46,
        P_KEY_SLASH         =     47,
        P_KEY_0             =     48,
        P_KEY_1             =     49,
        P_KEY_2             =     50,
        P_KEY_3             =     51,
        P_KEY_4             =     52,
        P_KEY_5             =     53,
        P_KEY_6             =     54,
        P_KEY_7             =     55,
        P_KEY_8             =     56,
        P_KEY_9             =     57,
        P_KEY_SEMICOLON     =     59,
        P_KEY_EQUAL         =     61,
        P_KEY_A             =     65,
        P_KEY_B             =     66,
        P_KEY_C             =     67,
        P_KEY_D             =     68,
        P_KEY_E             =     69,
        P_KEY_F             =     70,
        P_KEY_G             =     71,
        P_KEY_H             =     72,
        P_KEY_I             =     73,
        P_KEY_J             =     74,
        P_KEY_K             =     75,
        P_KEY_L             =     76,
        P_KEY_M             =     77,
        P_KEY_N             =     78,
        P_KEY_O             =     79,
        P_KEY_P             =     80,
        P_KEY_Q             =     81,
        P_KEY_R             =     82,
        P_KEY_S             =     83,
        P_KEY_T             =     84,
        P_KEY_U             =     85,
        P_KEY_V             =     86,
        P_KEY_W             =     87,
        P_KEY_X             =     88,
        P_KEY_Y             =     89,
        P_KEY_Z             =     90,
        P_KEY_LEFT_BRACKET  =     91,
        P_KEY_BACKSLASH     =     92, 
        P_KEY_RIGHT_BRACKET =     93, 
        P_KEY_GRAVE_ACCENT  =     96, 
        P_KEY_WORLD_1       =     161,
        P_KEY_WORLD_2       =     162,
        /* Function keys */
        P_KEY_ESCAPE        =     256,
        P_KEY_ENTER         =     257,
        P_KEY_TAB           =     258,
        P_KEY_BACKSPACE     =     259,
        P_KEY_INSERT        =     260,
        P_KEY_DELETE        =     261,
        P_KEY_RIGHT         =     262,
        P_KEY_LEFT          =     263,
        P_KEY_DOWN          =     264,
        P_KEY_UP            =     265,
        P_KEY_PAGE_UP       =     266,
        P_KEY_PAGE_DOWN     =     267,
        P_KEY_HOME          =     268,
        P_KEY_END           =     269,
        P_KEY_CAPS_LOCK     =     280,
        P_KEY_SCROLL_LOCK   =     281,
        P_KEY_NUM_LOCK      =     282,
        P_KEY_PRINT_SCREEN  =     283,
        P_KEY_PAUSE         =     284,
        P_KEY_F1            =     290,
        P_KEY_F2            =     291,
        P_KEY_F3            =     292,
        P_KEY_F4            =     293,
        P_KEY_F5            =     294,
        P_KEY_F6            =     295,
        P_KEY_F7            =     296,
        P_KEY_F8            =     297,
        P_KEY_F9            =     298,
        P_KEY_F10           =     299,
        P_KEY_F11           =     300,
        P_KEY_F12           =     301,
        P_KEY_F13           =     302,
        P_KEY_F14           =     303,
        P_KEY_F15           =     304,
        P_KEY_F16           =     305,
        P_KEY_F17           =     306,
        P_KEY_F18           =     307,
        P_KEY_F19           =     308,
        P_KEY_F20           =     309,
        P_KEY_F21           =     310,
        P_KEY_F22           =     311,
        P_KEY_F23           =     312,
        P_KEY_F24           =     313,
        P_KEY_F25           =     314,
        P_KEY_KP_0          =     320,
        P_KEY_KP_1          =     321,
        P_KEY_KP_2          =     322,
        P_KEY_KP_3          =     323,
        P_KEY_KP_4          =     324,
        P_KEY_KP_5          =     325,
        P_KEY_KP_6          =     326,
        P_KEY_KP_7          =     327,
        P_KEY_KP_8          =     328,
        P_KEY_KP_9          =     329,
        P_KEY_KP_DECIMAL    =     330,
        P_KEY_KP_DIVIDE     =     331,
        P_KEY_KP_MULTIPLY   =     332,
        P_KEY_KP_SUBTRACT   =     333,
        P_KEY_KP_ADD        =     334,
        P_KEY_KP_ENTER      =     335,
        P_KEY_KP_EQUAL      =     336,
        P_KEY_LEFT_SHIFT    =     340,
        P_KEY_LEFT_CONTROL  =     341,
        P_KEY_LEFT_ALT      =     342,
        P_KEY_LEFT_SUPER    =     343,
        P_KEY_RIGHT_SHIFT   =     344,
        P_KEY_RIGHT_CONTROL =     345,
        P_KEY_RIGHT_ALT     =     346,
        P_KEY_RIGHT_SUPER   =     347,
        P_KEY_MENU          =     348,
    };
}

#endif