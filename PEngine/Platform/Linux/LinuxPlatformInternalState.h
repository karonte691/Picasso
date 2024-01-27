#pragma once

#ifndef LINUX_PLATFORM_INTERNAL_STATE_H
#define LINUX_PLATFORM_INTERNAL_STATE_H

#include <xcb/xcb.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <PEngine/PBuild.h>

#if PICASSO_VULKAN_BUILD
#include <vulkan/vulkan.h>
#elif PICASSO_OPENGL_BUILD
#include <Glew/glew.h>
#include <GL/glx.h>
#endif

namespace Picasso::Engine::Platform
{
    struct LinuxPlatformInternalState
    {
        Display *display;
        xcb_connection_t *connection;
        xcb_window_t window;
        xcb_screen_t *screen;
        xcb_atom_t wmDeleteProtocols;
        xcb_atom_t wmDestroyWindow;
        int screenCount;

#if PICASSO_VULKAN_BUILD
        VkSurfaceKHR surface;
#elif PICASSO_OPENGL_BUILD
        GLXWindow glxwindow = 0;
#endif
    };
}

#endif
