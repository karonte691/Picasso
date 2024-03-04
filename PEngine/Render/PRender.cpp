/**
 * @file PRender.cpp
 * @brief Implementation of the PRender class.
 */
#include <PEngine/Render/PRender.h>

namespace Picasso::Engine::Render
{
    using Picasso::Engine::Render::Core::RDRIVERS;

    /**
     * @brief Initializes the PRender class.
     *
     * This method initializes the PRender class by creating the internal render and setting up the render data.
     *
     * @param appName The name of the application.
     * @param pState Pointer to the platform state.
     * @param engineState Pointer to the engine state.
     * @return Returns true if initialization is successful, false otherwise.
     */
    bool PRender::Init(const char *appName, PPlatformState *pState, EngineState *engineState)
    {
        if (m_renderData != nullptr)
        {
            Picasso::Engine::Logger::Logger::Warn("Trying to call Init() method of PRender class again...ignoring and quitting");
            return true;
        }

        m_internalRender = std::make_unique<RAPICore>();
        m_renderData = std::make_unique<RAPIData>();

        if (!m_internalRender->Create(appName, RDRIVERS::OPEN_GL, pState, engineState, m_renderData.get()))
        {
            Picasso::Engine::Logger::Logger::Fatal("Error trying to setup the internal render...");
            return false;
        }

        return true;
    }

    /**
     * @brief Shuts down the PRender class.
     *
     * This method shuts down the PRender class by releasing the render data and destroying the internal render.
     */
    void PRender::Shutdown()
    {
        m_renderData.reset();
        m_internalRender->Destroy();
    }

    /**
     * @brief Renders a frame.
     *
     * This method renders a frame using the internal render.
     *
     * @param rData Pointer to the render data.
     * @param pState Pointer to the platform state.
     * @return Returns true if rendering is successful, false otherwise.
     */
    bool PRender::RenderFrame(RenderData *rData, PPlatformState *pState)
    {
        if (m_renderData == nullptr)
        {
            Picasso::Engine::Logger::Logger::Warn("Trying to call RenderFrame() method of PRender class without proper Init() before...ignoring and quitting");
            return true;
        }

        // rendering the frame...
        if (m_internalRender->BeginFrame(m_renderData.get(), rData->deltaTime, pState))
        {
            if (!m_internalRender->EndFrame(m_renderData.get(), rData->deltaTime, pState))
            {
                Picasso::Engine::Logger::Logger::Error("Unable to rendering the frame...");
                return false;
            }

            m_renderData->frameNumber++;
            // Picasso::Engine::Logger::Logger::Debug("Render frame completed succesfully");
        }

        return true;
    }

    /**
     * @brief Handles the resize event.
     *
     * This method handles the resize event by resizing the render data.
     *
     * @param width The new width of the render area.
     * @param height The new height of the render area.
     */
    void PRender::OnResize(u_int16_t width, u_int16_t height)
    {
        m_internalRender->Resize(m_renderData.get(), width, height);
    }
}