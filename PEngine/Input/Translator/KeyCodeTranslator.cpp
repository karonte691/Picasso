#include <PEngine/Input/Translator/KeyCodeTranslator.h>

#include <X11/keysym.h>
#include <unordered_map>

namespace Picasso::Engine::Input::Translators
{
    KEYS KeyCodeTranslator::TranslateKey(uint32_t keyCode)
    {
        // Crea una mappa che associa i codici X11 a KEYS
        static const std::unordered_map<uint32_t, KEYS> keyMap = {
            {XK_BackSpace, P_KEY_BACKSPACE},
            {XK_Return, P_KEY_ENTER},
            {XK_Tab, P_KEY_TAB},
            {XK_Pause, P_KEY_PAUSE},
            {XK_Caps_Lock, P_KEY_CAPS_LOCK},
            {XK_Escape, P_KEY_ESCAPE},
            {XK_space, P_KEY_SPACE},
            {XK_End, P_KEY_END},
            {XK_Home, P_KEY_HOME},
            {XK_Left, P_KEY_LEFT},
            {XK_Up, P_KEY_UP},
            {XK_Right, P_KEY_RIGHT},
            {XK_Down, P_KEY_DOWN},
            {XK_Insert, P_KEY_INSERT},
            {XK_Delete, P_KEY_DELETE},
            {XK_F1, P_KEY_F1},
            {XK_F2, P_KEY_F2},
            {XK_F3, P_KEY_F3},
            {XK_F4, P_KEY_F4},
            {XK_F5, P_KEY_F5},
            {XK_F6, P_KEY_F6},
            {XK_F7, P_KEY_F7},
            {XK_F8, P_KEY_F8},
            {XK_F9, P_KEY_F9},
            {XK_F10, P_KEY_F10},
            {XK_F11, P_KEY_F11},
            {XK_F12, P_KEY_F12},
            {XK_F13, P_KEY_F13},
            {XK_F14, P_KEY_F14},
            {XK_F15, P_KEY_F15},
            {XK_F16, P_KEY_F16},
            {XK_F17, P_KEY_F17},
            {XK_F18, P_KEY_F18},
            {XK_F19, P_KEY_F19},
            {XK_F20, P_KEY_F20},
            {XK_F21, P_KEY_F21},
            {XK_F22, P_KEY_F22},
            {XK_F23, P_KEY_F23},
            {XK_F24, P_KEY_F24},
            {XK_Num_Lock, P_KEY_NUM_LOCK},
            {XK_Scroll_Lock, P_KEY_SCROLL_LOCK},
            {XK_KP_Equal, P_KEY_KP_EQUAL},
            {XK_Shift_L, P_KEY_LEFT_SHIFT},
            {XK_Shift_R, P_KEY_RIGHT_SHIFT},
            {XK_Control_L, P_KEY_LEFT_CONTROL},
            {XK_Control_R, P_KEY_RIGHT_CONTROL},
            {XK_semicolon, P_KEY_SEMICOLON},
            {XK_comma, P_KEY_COMMA},
            {XK_minus, P_KEY_MINUS},
            {XK_period, P_KEY_PERIOD},
            {XK_slash, P_KEY_SLASH},
            {XK_grave, P_KEY_GRAVE_ACCENT},
            {XK_a, P_KEY_A},
            {XK_A, P_KEY_A},
            {XK_b, P_KEY_B},
            {XK_B, P_KEY_B},
            {XK_c, P_KEY_C},
            {XK_C, P_KEY_C},
            {XK_d, P_KEY_D},
            {XK_D, P_KEY_D},
            {XK_e, P_KEY_E},
            {XK_E, P_KEY_E},
            {XK_f, P_KEY_F},
            {XK_F, P_KEY_F},
            {XK_g, P_KEY_G},
            {XK_G, P_KEY_G},
            {XK_h, P_KEY_H},
            {XK_H, P_KEY_H},
            {XK_i, P_KEY_I},
            {XK_I, P_KEY_I},
            {XK_j, P_KEY_J},
            {XK_J, P_KEY_J},
            {XK_k, P_KEY_K},
            {XK_K, P_KEY_K},
            {XK_l, P_KEY_L},
            {XK_L, P_KEY_L},
            {XK_m, P_KEY_M},
            {XK_M, P_KEY_M},
            {XK_n, P_KEY_N},
            {XK_N, P_KEY_N},
            {XK_o, P_KEY_O},
            {XK_O, P_KEY_O},
            {XK_p, P_KEY_P},
            {XK_P, P_KEY_P},
            {XK_q, P_KEY_Q},
            {XK_Q, P_KEY_Q},
            {XK_r, P_KEY_R},
            {XK_R, P_KEY_R},
            {XK_s, P_KEY_S},
            {XK_S, P_KEY_S},
            {XK_t, P_KEY_T},
            {XK_T, P_KEY_T},
            {XK_u, P_KEY_U},
            {XK_U, P_KEY_U},
            {XK_v, P_KEY_V},
            {XK_V, P_KEY_V},
            {XK_w, P_KEY_W},
            {XK_W, P_KEY_W},
            {XK_x, P_KEY_X},
            {XK_X, P_KEY_X},
            {XK_y, P_KEY_Y},
            {XK_Y, P_KEY_Y},
            {XK_z, P_KEY_Z},
            {XK_Z, P_KEY_Z}
        };

        // Cerca il codice nella mappa e restituisce il valore corrispondente
        const auto it = keyMap.find(keyCode);
        if (it != keyMap.end())
        {
            return it->second;
        }

        // Restituisci un valore predefinito o gestisci il caso non trovato come desideri
        return P_KEY_UNKNOWN;
    }
}