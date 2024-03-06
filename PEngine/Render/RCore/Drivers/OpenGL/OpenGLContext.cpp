#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLContext.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    /**
     * @brief Retrieves the GLX context for the specified platform state.
     *
     * @param pState The platform state.
     * @return The GLX context.
     */
    GLXContext OpenGLContext::Get(PPlatformState *pState)
    {
        int numFbConfigs = 0;
        int visualId = 0;
        int defaultScreen = DefaultScreen(pState->state->display);

        p_FbConfigs = glXChooseFBConfig(pState->state->display, defaultScreen, visualAttribs, &numFbConfigs);

        if (!p_FbConfigs || numFbConfigs == 0)
        {
            Picasso::Engine::Logger::Logger::Error("Cannot getglXGetFBConfigs data");

            this->ClearFrameBufferConfig();

            return nullptr;
        }

        GLXFBConfig fbConfig = p_FbConfigs[0];

        glXGetFBConfigAttrib(pState->state->display, fbConfig, GLX_VISUAL_ID, &visualId);

        return glXCreateNewContext(pState->state->display, fbConfig, GLX_RGBA_TYPE, 0, True);
    }

    /**
     * @brief Retrieves the frame buffer configuration.
     *
     * @return The frame buffer configuration.
     */
    GLXFBConfig *OpenGLContext::GetFrameBufferConfig()
    {
        return p_FbConfigs;
    }

    /**
     * @return True if the current context was set successfully, false otherwise.
     */
    bool OpenGLContext::SetCurrentContext(PPlatformState *pState, GLXContext context, GLXWindow window)
    {
        return glXMakeContextCurrent(pState->state->display, window, window, context);
    }

    /**
     * @brief Clears the frame buffer configuration.
     */
    void OpenGLContext::ClearFrameBufferConfig()
    {
        XFree(p_FbConfigs);
        p_FbConfigs = nullptr;
    }

    /**
     * @brief Destroys the GLX context for the specified platform state.
     *
     * @param pState The platform state.
     * @param context The GLX context to destroy.
     */
    void OpenGLContext::DestroyContext(PPlatformState *pState, GLXContext context)
    {
        glXDestroyContext(pState->state->display, context);
        this->ClearFrameBufferConfig();
    }
}