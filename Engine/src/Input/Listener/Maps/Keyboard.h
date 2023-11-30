#pragma once

#ifndef KEYBOARD_H
#define KEYBOARD_H

namespace Picasso::Engine::Input
{
    enum KEYS
    {
        //from P3.h
        /* The unknown key */
        #define P_KEY_UNKNOWN            -1

        /* Printable keys */
        #define P_KEY_SPACE              32
        #define P_KEY_APOSTROPHE         39  /* ' */
        #define P_KEY_COMMA              44  /* , */
        #define P_KEY_MINUS              45  /* - */
        #define P_KEY_PERIOD             46  /* . */
        #define P_KEY_SLASH              47  /* / */
        #define P_KEY_0                  48
        #define P_KEY_1                  49
        #define P_KEY_2                  50
        #define P_KEY_3                  51
        #define P_KEY_4                  52
        #define P_KEY_5                  53
        #define P_KEY_6                  54
        #define P_KEY_7                  55
        #define P_KEY_8                  56
        #define P_KEY_9                  57
        #define P_KEY_SEMICOLON          59  /* ; */
        #define P_KEY_EQUAL              61  /* = */
        #define P_KEY_A                  65
        #define P_KEY_B                  66
        #define P_KEY_C                  67
        #define P_KEY_D                  68
        #define P_KEY_E                  69
        #define P_KEY_F                  70
        #define P_KEY_G                  71
        #define P_KEY_H                  72
        #define P_KEY_I                  73
        #define P_KEY_J                  74
        #define P_KEY_K                  75
        #define P_KEY_L                  76
        #define P_KEY_M                  77
        #define P_KEY_N                  78
        #define P_KEY_O                  79
        #define P_KEY_P                  80
        #define P_KEY_Q                  81
        #define P_KEY_R                  82
        #define P_KEY_S                  83
        #define P_KEY_T                  84
        #define P_KEY_U                  85
        #define P_KEY_V                  86
        #define P_KEY_W                  87
        #define P_KEY_X                  88
        #define P_KEY_Y                  89
        #define P_KEY_Z                  90
        #define P_KEY_LEFT_BRACKET       91  /* [ */
        #define P_KEY_BACKSLASH          92  /* \ */
        #define P_KEY_RIGHT_BRACKET      93  /* ] */
        #define P_KEY_GRAVE_ACCENT       96  /* ` */
        #define P_KEY_WORLD_1            161 /* non-US #1 */
        #define P_KEY_WORLD_2            162 /* non-US #2 */

        /* Function keys */
        #define P_KEY_ESCAPE             256
        #define P_KEY_ENTER              257
        #define P_KEY_TAB                258
        #define P_KEY_BACKSPACE          259
        #define P_KEY_INSERT             260
        #define P_KEY_DELETE             261
        #define P_KEY_RIGHT              262
        #define P_KEY_LEFT               263
        #define P_KEY_DOWN               264
        #define P_KEY_UP                 265
        #define P_KEY_PAGE_UP            266
        #define P_KEY_PAGE_DOWN          267
        #define P_KEY_HOME               268
        #define P_KEY_END                269
        #define P_KEY_CAPS_LOCK          280
        #define P_KEY_SCROLL_LOCK        281
        #define P_KEY_NUM_LOCK           282
        #define P_KEY_PRINT_SCREEN       283
        #define P_KEY_PAUSE              284
        #define P_KEY_F1                 290
        #define P_KEY_F2                 291
        #define P_KEY_F3                 292
        #define P_KEY_F4                 293
        #define P_KEY_F5                 294
        #define P_KEY_F6                 295
        #define P_KEY_F7                 296
        #define P_KEY_F8                 297
        #define P_KEY_F9                 298
        #define P_KEY_F10                299
        #define P_KEY_F11                300
        #define P_KEY_F12                301
        #define P_KEY_F13                302
        #define P_KEY_F14                303
        #define P_KEY_F15                304
        #define P_KEY_F16                305
        #define P_KEY_F17                306
        #define P_KEY_F18                307
        #define P_KEY_F19                308
        #define P_KEY_F20                309
        #define P_KEY_F21                310
        #define P_KEY_F22                311
        #define P_KEY_F23                312
        #define P_KEY_F24                313
        #define P_KEY_F25                314
        #define P_KEY_KP_0               320
        #define P_KEY_KP_1               321
        #define P_KEY_KP_2               322
        #define P_KEY_KP_3               323
        #define P_KEY_KP_4               324
        #define P_KEY_KP_5               325
        #define P_KEY_KP_6               326
        #define P_KEY_KP_7               327
        #define P_KEY_KP_8               328
        #define P_KEY_KP_9               329
        #define P_KEY_KP_DECIMAL         330
        #define P_KEY_KP_DIVIDE          331
        #define P_KEY_KP_MULTIPLY        332
        #define P_KEY_KP_SUBTRACT        333
        #define P_KEY_KP_ADD             334
        #define P_KEY_KP_ENTER           335
        #define P_KEY_KP_EQUAL           336
        #define P_KEY_LEFT_SHIFT         340
        #define P_KEY_LEFT_CONTROL       341
        #define P_KEY_LEFT_ALT           342
        #define P_KEY_LEFT_SUPER         343
        #define P_KEY_RIGHT_SHIFT        344
        #define P_KEY_RIGHT_CONTROL      345
        #define P_KEY_RIGHT_ALT          346
        #define P_KEY_RIGHT_SUPER        347
        #define P_KEY_MENU               348
    };
}

#endif