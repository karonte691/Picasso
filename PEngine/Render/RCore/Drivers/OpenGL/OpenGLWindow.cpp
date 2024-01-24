#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLWindow.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    GLXWindow OpenGLWindow::Get(std::shared_ptr<PPlatformState> pState, GLXFBConfig *frameBufferConfigs)
    {
        GLXDrawable drawable = 0;

        GLXWindow glxwindow = glXCreateWindow(pState->state->display, *frameBufferConfigs, pState->state->window, 0);

        return glxwindow;
    }
}