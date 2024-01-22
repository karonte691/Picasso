#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLDriver.h>

#include <GL/glx.h>
#include <GL/gl.h>

namespace Picasso::Engine::Render::Core::Drivers
{
    static int visualAttribs[] =
        {
            GLX_X_RENDERABLE, True,
            GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
            GLX_RENDER_TYPE, GLX_RGBA_BIT,
            GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
            GLX_RED_SIZE, 8,
            GLX_GREEN_SIZE, 8,
            GLX_BLUE_SIZE, 8,
            GLX_ALPHA_SIZE, 8,
            GLX_DEPTH_SIZE, 24,
            GLX_STENCIL_SIZE, 8,
            GLX_DOUBLEBUFFER, True,
            None};

    bool OpenGLDriver::InitDriver(std::shared_ptr<RAPIData> rcData, const char *appName, std::shared_ptr<PPlatformState> pState, EngineState *eState)
    {
        p_Context = new DriverContext();

        p_Context->frameBufferWidth = eState->width > 0 ? eState->width : PICASSO_DEFAULT_WIDTH;
        p_Context->frameBufferHeight = eState->height > 0 ? eState->height : PICASSO_DEFAULT_HEIGHT;

        p_PlatformState = pState;

        if (!this->_InitOpenGl())
        {
            Picasso::Engine::Logger::Logger::Error("Cannot initialize opengl driver!");
            return false;
        }

        return true;
    }

    void OpenGLDriver::Shutdown()
    {
        if (p_Context != nullptr)
        {
            if (p_Context->glxwindow != 0)
            {
                glXDestroyWindow(p_PlatformState->state->display, p_Context->glxwindow);
            }

            if (p_Context->glxContext != 0)
            {
                glXDestroyContext(p_PlatformState->state->display, p_Context->glxContext);
            }

            delete p_Context;
            p_Context = nullptr;
        }
    }

    bool OpenGLDriver::_InitOpenGl()
    {
        int numFbConfigs = 0;
        int visualId = 0;
        int defaultScreen = DefaultScreen(p_PlatformState->state->display);

        GLXFBConfig *fbConfigs = glXChooseFBConfig(p_PlatformState->state->display, defaultScreen, visualAttribs, &numFbConfigs);

        if (!fbConfigs || numFbConfigs == 0)
        {
            Picasso::Engine::Logger::Logger::Error("Cannot getglXGetFBConfigs data");
            return false;
        }

        GLXFBConfig fb_config = fbConfigs[0];

        glXGetFBConfigAttrib(p_PlatformState->state->display, fb_config, GLX_VISUAL_ID, &visualId);

        GLXContext context = glXCreateNewContext(p_PlatformState->state->display, fb_config, GLX_RGBA_TYPE, 0, True);
        if (!context)
        {
            Picasso::Engine::Logger::Logger::Error("glXCreateNewContext returned an error");
            return false;
        }

        /* Create GLX Window */
        GLXDrawable drawable = 0;

        GLXWindow glxwindow = glXCreateWindow(p_PlatformState->state->display, *fbConfigs, p_PlatformState->state->window, 0);

        if (!p_PlatformState->state->window)
        {
            glXDestroyContext(p_PlatformState->state->display, context);

            Picasso::Engine::Logger::Logger::Error("glXCreateWindow returned an error\n");
            return false;
        }

        drawable = glxwindow;

        bool glxMakeCtxCurrentRes = glXMakeContextCurrent(p_PlatformState->state->display, drawable, drawable, context);

        if (!glxMakeCtxCurrentRes)
        {
            glXDestroyContext(p_PlatformState->state->display, context);

            Picasso::Engine::Logger::Logger::Error("Cannot set glx current context\n");
            return false;
        }

        p_Context->glxContext = context;
        p_Context->glxwindow = glxwindow;

        delete fbConfigs;

        return true;
    }
}