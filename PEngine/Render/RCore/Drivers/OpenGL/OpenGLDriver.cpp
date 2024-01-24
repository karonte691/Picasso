#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLDriver.h>

#include <GL/glx.h>
#include <GL/gl.h>

namespace Picasso::Engine::Render::Core::Drivers
{

    bool OpenGLDriver::InitDriver(std::shared_ptr<RAPIData> rcData, const char *appName, std::shared_ptr<PPlatformState> pState, EngineState *eState)
    {
        p_Context = new Picasso::Engine::Render::Core::Drivers::OpenGL::DriverContext();
        p_OpenGLContext = new OpenGLContext();
        p_OpenGLWindow = new OpenGLWindow();

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

    bool OpenGLDriver::BeginFrame(std::shared_ptr<RAPIData> apiData, _Float32 deltaTime, std::shared_ptr<PPlatformState> pState)
    {
        glClearColor(0.2, 0.4, 0.9, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        return true;
    }

    bool OpenGLDriver::EndFrame(std::shared_ptr<RAPIData> apiData, _Float32 deltaTime, std::shared_ptr<PPlatformState> pState)
    {
        glXSwapBuffers(pState->state->display, p_Context->glxwindow);
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
        p_Context->glxwindow = glxWindow;

        p_OpenGLContext->ClearFrameBufferConfig();

        return true;
    }
}