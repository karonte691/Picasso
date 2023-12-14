#include <PEngine/Platform/Linux/PlatformInputManager.h>

namespace Picasso::Engine::Platform::Linux
{
    using Picasso::Engine::Input::KEYS;
    using Picasso::Engine::Input::BUTTONS;

    PlatformInputManager::PlatformInputManager()
    {
        m_keyboardListener = std::make_unique<KeyboardListener>();
        m_mouseListener = std::make_unique<MouseListener>();
        
        m_keyCodeTranslator = std::make_unique<KeyCodeTranslator>();
        m_mouseCodeTranslator = std::make_unique<MouseCodeTranslator>();
    }

    void PlatformInputManager::ProcessXCBKeyBoardEvent(xcb_generic_event_t* event, std::shared_ptr<LinuxPlatformInternalState> state, pInputState& inputState)
    {
        xcb_key_press_event_t* keyEvent = (xcb_key_press_event_t*)event;

        if(keyEvent == nullptr){
                        Picasso::Engine::Logger::Logger::Error("Error while casting event to keyEvent");
                        return;
        }

        bool keyPressed = event->response_type == XCB_KEY_PRESS;
        xcb_keycode_t kCode = keyEvent->detail;

        KeySym keySym = XkbKeycodeToKeysym(state->display, (KeyCode)kCode, 0, kCode & ShiftMask ? 1 : 0);
        KEYS keyValue = m_keyCodeTranslator->TranslateKey(keySym);

        if(keyValue == 0)
        {
            Picasso::Engine::Logger::Logger::Warn("Key event translated to P_KEY_UNKNOWN. Skipping event...");
            return;
        }

        m_keyboardListener->ProcessKey(keyValue, keyPressed, inputState);

        Picasso::Engine::Logger::Logger::Debug("Event XCB_KEY_PRESS|XCB_KEY_RELEASE received...");
        Picasso::Engine::Logger::Logger::Debug("Key %d pressed: %d", keyValue, keyPressed);
    }

    void PlatformInputManager::ProcessXCBMouseEvent(xcb_generic_event_t* event, std::shared_ptr<LinuxPlatformInternalState> state, pInputState& inputState)
    {
        xcb_button_press_event_t* buttonEvent = (xcb_button_press_event_t*)event;
        bool buttonPressed = event->response_type == XCB_BUTTON_PRESS;

        if(buttonEvent == nullptr){
            Picasso::Engine::Logger::Logger::Error("Error while casting event to buttonEvent");
            return;
        }
 
        BUTTONS buttonValue = m_mouseCodeTranslator->TranslateButton(buttonEvent->detail);

        if(buttonValue == -1)
        {
            Picasso::Engine::Logger::Logger::Error("Button event translated to P_MOUSE_BUTTON_UNKW. Skipping event...");
            return;
        }

        m_mouseListener->ProcessButton(buttonValue, buttonPressed, inputState);

        Picasso::Engine::Logger::Logger::Debug("Event XCB_BUTTON_PRESS|XCB_BUTTON_RELEASE received...");
        Picasso::Engine::Logger::Logger::Debug("Button %d pressed: %d", buttonValue, buttonPressed);
    }

    void PlatformInputManager::ProcessXCBMouseMovement(xcb_generic_event_t* event, pInputState& inputState)
    {
        xcb_motion_notify_event_t* movementEvent = (xcb_motion_notify_event_t*)event;

         if(movementEvent == nullptr){
            Picasso::Engine::Logger::Logger::Error("Error while casting event to buttonEvent");
            return;
        }

        m_mouseListener->ProcessMouseMove(movementEvent->event_x, movementEvent->event_y, inputState);

        Picasso::Engine::Logger::Logger::Debug("Event XCB_MOTION_NOTIFY received...");
        Picasso::Engine::Logger::Logger::Debug("x %d y: %d", movementEvent->event_x, movementEvent->event_y);
    }

    bool PlatformInputManager::ProcessXCBClientMessage(xcb_generic_event_t* event, std::shared_ptr<LinuxPlatformInternalState> state)
    {
        xcb_client_message_event_t* messageEvent = (xcb_client_message_event_t*)event;

         if(messageEvent == nullptr){
            Picasso::Engine::Logger::Logger::Error("Error while casting event to messageEvent");
            return false;
        }

        Picasso::Engine::Logger::Logger::Debug("Event XCB_CLIENT_MESSAGE received...");

        return messageEvent->data.data32[0] == state->wmDestroyWindow;
    }
}