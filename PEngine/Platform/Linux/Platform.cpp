#include <PEngine/Platform/Platform.h>

#include <xcb/xcb.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h>
#include <sys/time.h>
#include <time.h>
#include <cstdlib>
#include <cstdio>

#include <PEngine/Input/Maps/Keyboard.h>
#include <PEngine/Input/Maps/Mouse.h>
#include <unistd.h>

namespace Picasso::Engine::Platform
{
    using Picasso::Engine::EventSystem::PicassoRegistry;
    using Picasso::Engine::EventSystem::Events::PEvent;

    using Picasso::Engine::Input::BUTTONS;
    using Picasso::Engine::Input::KEYS;
    using Picasso::Engine::Input::pInputState;

    bool PPlatform::Init(std::string appName, int x, int y, int width, int height)
    {
        m_pstate = std::make_shared<LinuxPlatformInternalState>(LinuxPlatformInternalState{
            nullptr,
            nullptr,
            0,
            nullptr,
            0,
            0,
            0,
            nullptr});

        // connect to X Server
        m_pstate->display = XOpenDisplay(0);

        if (m_pstate->display == nullptr)
        {
            Picasso::Engine::Logger::Logger::Fatal("Display Connection NOT granted");
            return false;
        }

        Picasso::Engine::Logger::Logger::Debug("Display Connection granted");

        // This disable GLOBALLY(OS Speaking) the input auto repeat...
        // REMEMBER TO TURN IT ON AGAIN IN THE SHUTDOWN METHOD OTHERWISE...
        XAutoRepeatOff(m_pstate->display);
        m_pstate->screenCount = XScreenCount(m_pstate->display);

        Picasso::Engine::Logger::Logger::Debug("Screen detected %d", m_pstate->screenCount);

        // init XCB
        m_pstate->connection = XGetXCBConnection(m_pstate->display);

        if (m_pstate->connection == nullptr || xcb_connection_has_error(m_pstate->connection))
        {
            Picasso::Engine::Logger::Logger::Fatal("Unable to init xcb connection");
            return false;
        }

        Picasso::Engine::Logger::Logger::Debug("XCB Connection granted");

        const xcb_setup_t *setup = xcb_get_setup(m_pstate->connection);

        m_pstate->screen = xcb_setup_roots_iterator(setup).data;

        Picasso::Engine::Logger::Logger::Debug("Screen width detected: %d", m_pstate->screen->width_in_pixels);
        Picasso::Engine::Logger::Logger::Debug("Screen height detected: %d", m_pstate->screen->height_in_pixels);

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
            valueList);

        if (cookie.sequence == 0)
        {
            Picasso::Engine::Logger::Logger::Fatal("Unable to create XCB window");
            return false;
        }

        Picasso::Engine::Logger::Logger::Debug("XCB window created succesfully");

        // register destroy events
        this->_registerWindowDestroyEvent();

        xcb_void_cookie_t mappingCookie = xcb_map_window(m_pstate->connection, m_pstate->window);

        if (mappingCookie.sequence == 0)
        {
            Picasso::Engine::Logger::Logger::Fatal("Unable to map XCB window");
            return false;
        }

        // flush the stream
        int flushResult = xcb_flush(m_pstate->connection);

        if (flushResult <= 0)
        {
            Picasso::Engine::Logger::Logger::Fatal("Error while flushing xcb stream");
            return false;
        }

        Picasso::Engine::Logger::Logger::Debug("Platform setting up and flushing is completed.");

        // at this point, we init the input manager
        m_inputManager = std::make_unique<Picasso::Engine::Platform::Linux::PlatformInputManager>();

        // and a new inputState
        m_inputState = {};

        return true;
    }

    void PPlatform::Shutdown()
    {
        m_inputState = {}; // reset anyway

        XAutoRepeatOn(m_pstate->display);

        xcb_destroy_window(m_pstate->connection, m_pstate->window);
    }

    bool PPlatform::Process()
    {
        xcb_generic_event_t *event;
        xcb_client_message_event_t *clientMessange;
        bool quitRaised = false;

        while ((event = xcb_poll_for_event(m_pstate->connection)))
        {

            Picasso::Engine::Logger::Logger::Debug("Processing XCB event...");

            switch (event->response_type & ~0x80)
            {
            case XCB_KEY_PRESS:
            case XCB_KEY_RELEASE:
            {
                // keyboard input
                m_inputManager->ProcessXCBKeyBoardEvent(event, m_pstate, m_inputState);
            }
            break;
            case XCB_BUTTON_PRESS:
            case XCB_BUTTON_RELEASE:
            {
                // mouse input
                m_inputManager->ProcessXCBMouseEvent(event, m_pstate, m_inputState);
            }
            break;
            case XCB_MOTION_NOTIFY:
            {
                // mouse movement
                m_inputManager->ProcessXCBMouseMovement(event, m_inputState);
            }
            break;
            case XCB_CONFIGURE_NOTIFY:
                break;
            case XCB_EXPOSE:
                PicassoRegistry::Dispatch(PEvent::PLATFORM_EXPOSE);
                break;
            case XCB_CLIENT_MESSAGE:
            {
                // application event
                quitRaised = m_inputManager->ProcessXCBClientMessage(event, m_pstate);
            }
            break;
            default:
                break;
            }
        }

        return !quitRaised;
    }

    std::shared_ptr<PPlatformState> PPlatform::GetState()
    {
        auto pState = std::make_shared<PPlatformState>();

        pState->state = m_pstate;

        return pState;
    }

    int PPlatform::_getEventsMask() const
    {
        return XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    }

    unsigned int PPlatform::_getEventsValue() const
    {
        return XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE | XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_POINTER_MOTION | XCB_EVENT_MASK_STRUCTURE_NOTIFY;
    }

    void PPlatform::_registerWindowDestroyEvent()
    {
        xcb_intern_atom_cookie_t wmDeleteCookie = xcb_intern_atom(
            m_pstate->connection,
            0,
            m_strWmDeleteWindow.length(),
            m_strWmDeleteWindow.c_str());

        xcb_intern_atom_cookie_t wmProtocolsCookie = xcb_intern_atom(
            m_pstate->connection,
            0,
            m_strWmProtocols.length(),
            m_strWmProtocols.c_str());

        // reply
        xcb_intern_atom_reply_t *wmDeleteReply = xcb_intern_atom_reply(
            m_pstate->connection,
            wmDeleteCookie,
            nullptr);

        xcb_intern_atom_reply_t *wmProtocolsReply = xcb_intern_atom_reply(
            m_pstate->connection,
            wmProtocolsCookie,
            nullptr);

        if (!wmDeleteReply || !wmProtocolsReply)
        {
            Picasso::Engine::Logger::Logger::Error("Cannot register windowDestroyEvent");

            if (wmDeleteReply)
            {
                free(wmDeleteReply);
            }
            if (wmProtocolsReply)
            {
                free(wmProtocolsReply);
            }

            return;
        }
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
            &wmDeleteReply->atom);

        if (wmDeleteReply)
        {
            free(wmDeleteReply);
        }
        if (wmProtocolsReply)
        {
            free(wmProtocolsReply);
        }
    }
}
