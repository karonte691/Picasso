#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLDriver.h>

#include <Glew/glew.h>
#include <GL/glx.h>
#include <GL/gl.h>

namespace Picasso::Engine::Render::Core::Drivers
{
    bool OpenGLDriver::InitDriver(RAPIData *rcData, const char *appName, PPlatformState *pState, EngineState *eState)
    {
        p_Context = new Picasso::Engine::Render::Core::Drivers::OpenGL::DriverContext();
        p_OpenGLContext = new OpenGLContext();
        p_OpenGLWindow = new OpenGLWindow();

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
            if (p_PlatformState->state->glxwindow != 0)
            {
                glXDestroyWindow(p_PlatformState->state->display, p_PlatformState->state->glxwindow);
            }

            if (p_Context->glxContext != 0)
            {
                glXDestroyContext(p_PlatformState->state->display, p_Context->glxContext);
            }

            delete p_Context;
            p_Context = nullptr;
        }

        if (p_OpenGLContext != nullptr)
        {
            delete p_OpenGLContext;
            p_OpenGLContext = nullptr;
        }

        if (p_OpenGLWindow != nullptr)
        {
            delete p_OpenGLWindow;
            p_OpenGLWindow = nullptr;
        }
    }

    void OpenGLDriver::OnResize(u_int16_t width, u_int16_t height)
    {
    }

    bool OpenGLDriver::BeginFrame(RAPIData *apiData, float deltaTime, PPlatformState *pState)
    {
        glClearColor(0.25f, 0.5f, 0.75f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        return true;
    }

    bool OpenGLDriver::EndFrame(RAPIData *apiData, float deltaTime, PPlatformState *pState)
    {
        glXSwapBuffers(pState->state->display, p_PlatformState->state->glxwindow);
        glFlush();

        return true;
    }

    bool OpenGLDriver::_InitOpenGl()
    {
        GLXContext context = p_OpenGLContext->Get(p_PlatformState);

        if (!context)
        {
            Picasso::Engine::Logger::Logger::Error("glXCreateNewContext returned an error");

            p_OpenGLContext->ClearFrameBufferConfig();

            return false;
        }

        GLXFBConfig *frameBufferConfigs = p_OpenGLContext->GetFrameBufferConfig();

        if (!p_PlatformState->state->window)
        {
            p_OpenGLContext->DestroyContext(p_PlatformState, context);

            Picasso::Engine::Logger::Logger::Error("glXCreateWindow returned an error\n");

            return false;
        }

        GLXWindow glxWindow = p_OpenGLWindow->Get(p_PlatformState, frameBufferConfigs);

        if (!p_OpenGLContext->SetCurrentContext(p_PlatformState, context, glxWindow))
        {
            p_OpenGLContext->DestroyContext(p_PlatformState, context);

            Picasso::Engine::Logger::Logger::Error("Cannot set glx current context\n");

            return false;
        }

        p_Context->glxContext = context;
        p_PlatformState->state->glxwindow = glxWindow;

        p_OpenGLContext->ClearFrameBufferConfig();

        glewExperimental = GL_TRUE;

        if (glewInit() != GLEW_OK)
        {
            p_OpenGLContext->DestroyContext(p_PlatformState, context);

            Picasso::Engine::Logger::Logger::Error("Cannot init glew!\n");

            return false;
        }

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        Picasso::Engine::Logger::Logger::Debug("Driver OpenGL  set up succesfully");

        return true;
    }

    RDRIVERS OpenGLDriver::GetType()
    {
        return RDRIVERS::OPEN_GL;
    }
}