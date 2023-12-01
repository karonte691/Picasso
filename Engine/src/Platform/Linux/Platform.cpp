#include "Platform/Platform.h"

#include <xcb/xcb.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h>
#include <sys/time.h>
#include <time.h>
#include <cstdlib>
#include <cstdio>


#include "Input/Maps/Keyboard.h"

namespace Picasso::Engine::Platform
{
    using Picasso::Engine::Input::KEYS;
    using Picasso::Engine::Input::pInputState;

    bool PPlatform::Init(std::string appName, int x, int y, int width, int height)
    {
        m_pstate = std::make_unique<LinuxPlatformInternalState>(LinuxPlatformInternalState{
            nullptr,
            nullptr,
            0,
            nullptr,
            0,
            0,
            0,
        });

        //connect to X Server
        m_pstate->display = XOpenDisplay(0);
        
        if(m_pstate->display == nullptr)
        {
            Picasso::Logger::Logger::Fatal("Display Connection NOT granted");
            return false;
        }

        Picasso::Logger::Logger::Debug("Display Connection granted");

        //This disable GLOBALLY(OS Speaking) the input auto repeat...
        //REMEMBER TO TURN IT ON AGAIN IN THE SHUTDOWN METHOD OTHERWISE...
        XAutoRepeatOff(m_pstate->display);
        m_pstate->screenCount = XScreenCount(m_pstate->display);

        Picasso::Logger::Logger::FDebug("Screen detected %d", m_pstate->screenCount);

        //init XCB
        m_pstate->connection = XGetXCBConnection(m_pstate->display);

        if(m_pstate->connection == nullptr || xcb_connection_has_error(m_pstate->connection))
        {
            Picasso::Logger::Logger::Fatal("Unable to init xcb connection");
            return false;
        }


        Picasso::Logger::Logger::Debug("XCB Connection granted");

        const xcb_setup_t* setup = xcb_get_setup(m_pstate->connection);
        
        m_pstate->screen  = xcb_setup_roots_iterator(setup).data;

        Picasso::Logger::Logger::FDebug("Screen width detected: %d", m_pstate->screen->width_in_pixels);
        Picasso::Logger::Logger::FDebug("Screen height detected: %d", m_pstate->screen->height_in_pixels);

        m_pstate->window = xcb_generate_id(m_pstate->connection);

        int eventsMask = this->_getEventsMask();
        u_int32_t eventValues = this->_getEventsValue();
        u_int32_t valueList[] = {m_pstate->screen->black_pixel, eventValues};

        xcb_void_cookie_t cookie = xcb_create_window(
            m_pstate->connection,
            XCB_COPY_FROM_PARENT,
            m_pstate->window,
            m_pstate->screen->root,
            x,
            y,
            width,
            height,
            0,
            XCB_WINDOW_CLASS_INPUT_OUTPUT,
            m_pstate->screen->root_visual,
            eventsMask,
            valueList
        );
        
        if(cookie.sequence == 0)
        {
            Picasso::Logger::Logger::Fatal("Unable to create XCB window");
            return false;
        }

        Picasso::Logger::Logger::Debug("XCB window created succesfully");

        //change window title
        xcb_change_property(
            m_pstate->connection,
            XCB_PROP_MODE_REPLACE,
            m_pstate->window,
            XCB_ATOM_WM_NAME,
            XCB_ATOM_STRING,
            0,
            appName.length(),
            appName.c_str()
        );

        //register destroy events
        this->_registerWindowDestroyEvent();

        xcb_void_cookie_t mappingCookie = xcb_map_window(m_pstate->connection, m_pstate->window);

        if(mappingCookie.sequence == 0)
        {
            Picasso::Logger::Logger::Fatal("Unable to map XCB window");
            return false;
        }

        //flush the stream
        int flushResult = xcb_flush(m_pstate->connection);

        if(flushResult <= 0)
        {
            Picasso::Logger::Logger::Fatal("Error while flushing xcb stream");
            return false;
        }

        Picasso::Logger::Logger::Debug("Platform setting up and flushing is completed.");

        //at this point, we instanciate the KeyboardListener module
        m_keyboardListener = std::make_unique<KeyboardListener>();
        //and a new inputState
        m_inputState = {};

        return true;
    }


    void PPlatform::Shutdown()
    {
        m_inputState = {}; //reset anyway

        XAutoRepeatOn(m_pstate->display);

        xcb_destroy_window(m_pstate->connection, m_pstate->window);
    }

    bool PPlatform::Process()
    {
        if(m_keyCodeTranslator == nullptr)
        {
            //instance the keyboard translator
            m_keyCodeTranslator = std::make_unique<KeyCodeTranslator>();
        }

        xcb_generic_event_t* event;
        xcb_client_message_event_t* clientMessange;
        bool quitRaised = false;

        while ((event = xcb_poll_for_event(m_pstate->connection))) {
           
            Picasso::Logger::Logger::Debug("Processing XCB event...");

            switch(event->response_type & ~0x80)
            {
                case XCB_KEY_PRESS:
                case XCB_KEY_RELEASE:
                {
                    //keyboard input
                    xcb_key_press_event_t* keyEvent = (xcb_key_press_event_t*)event;

                    if(keyEvent == nullptr){
                        Picasso::Logger::Logger::Error("Error while casting event to keyEvent");
                        continue;
                    }

                    bool keyPressed = event->response_type == XCB_KEY_PRESS;
                    xcb_keycode_t kCode = keyEvent->detail;

                    KeySym keySym = XkbKeycodeToKeysym(m_pstate->display, (KeyCode)kCode, 0, kCode & ShiftMask ? 1 : 0);

                    KEYS keyValue = m_keyCodeTranslator->TranslateKey(keySym);

                    if(keyValue == 0)
                    {
                        Picasso::Logger::Logger::Warn("Key event translated to P_KEY_UNKNOWN. Skipping event...");
                        continue;
                    }

                    Picasso::Logger::Logger::Debug("Event XCB_KEY_PRESS|XCB_KEY_RELEASE received...");
                    Picasso::Logger::Logger::FDebug("Key %d pressed: %d", keyValue, keyPressed);

                    m_keyboardListener->ProcessKey(keyValue, keyPressed, m_inputState);
                    
                }   break;
                case XCB_BUTTON_PRESS:
                case XCB_BUTTON_RELEASE:
                    Picasso::Logger::Logger::Debug("Event XCB_BUTTON_PRESS|XCB_BUTTON_RELEASE received...");
                    //mouse input
                    break;
                case XCB_MOTION_NOTIFY:
                    //mouse movement
                    Picasso::Logger::Logger::Debug("Event XCB_MOTION_NOTIFY received...");
                    break;
                case XCB_CONFIGURE_NOTIFY:
                    Picasso::Logger::Logger::Debug("Event XCB_CONFIGURE_NOTIFY received...");
                    //resize
                    break;
                case XCB_EXPOSE:
                    Picasso::Logger::Logger::Debug("Event XCB_EXPOSE received...");
                    break;
                case XCB_CLIENT_MESSAGE:
                {
                    Picasso::Logger::Logger::Debug("Event XCB_CLIENT_MESSAGE received...");

                    clientMessange = (xcb_client_message_event_t*)event;

                    if(clientMessange->data.data32[0] == m_pstate->wmDestroyWindow)
                    {
                        Picasso::Logger::Logger::Info("Quit event raised");
                        quitRaised = true;
                    }
                } break;
                default:
                    break;
            }
        } 

        return !quitRaised;
    }

    int PPlatform::_getEventsMask() const
    {
        return XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    }

    unsigned int PPlatform::_getEventsValue() const
    {
        return  XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE 
                | XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE
                | XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_POINTER_MOTION 
                | XCB_EVENT_MASK_STRUCTURE_NOTIFY;
    }

    void PPlatform::_registerWindowDestroyEvent()
    {
        xcb_intern_atom_cookie_t wmDeleteCookie = xcb_intern_atom(
            m_pstate->connection,
            0,
            m_strWmDeleteWindow.length(),
            m_strWmDeleteWindow.c_str()
        );

        xcb_intern_atom_cookie_t wmProtocolsCookie = xcb_intern_atom(
            m_pstate->connection,
            0,
            m_strWmProtocols.length(),
            m_strWmProtocols.c_str()
        );


        //reply
        xcb_intern_atom_reply_t* wmDeleteReply = xcb_intern_atom_reply(
            m_pstate->connection,
            wmDeleteCookie,
            nullptr
        );

        xcb_intern_atom_reply_t* wmProtocolsReply = xcb_intern_atom_reply(
            m_pstate->connection,
            wmProtocolsCookie,
            nullptr
        );

        m_pstate->wmDestroyWindow = wmDeleteReply->atom;
        m_pstate->wmDeleteProtocols = wmProtocolsReply->atom;

        xcb_change_property(
            m_pstate->connection,
            XCB_PROP_MODE_REPLACE,
            m_pstate->window,
            wmProtocolsReply->atom,
            4,
            32,
            1,
            &wmDeleteReply->atom
        );
    }
}
