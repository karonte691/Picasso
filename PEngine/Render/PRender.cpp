#include <PEngine/Render/PRender.h>

namespace Picasso::Engine::Render
{
    using Picasso::Engine::Render::Core::RDRIVERS;

    bool PRender::Init(const char *appName, EngineState *platformState)
    {
        if (m_renderData != nullptr)
        {
            Picasso::Logger::Logger::Warn("Trying to call Init() method of PRender class again...ignoring and quitting");
            return true;
        }

        m_internalRender = std::make_unique<RAPICore>();
        m_renderData = std::make_shared<RAPIData>();

        if (!m_internalRender->Create(appName, RDRIVERS::VULKAN, platformState, m_renderData))
        {
            Picasso::Logger::Logger::Fatal("Error trying to setup the internal render...");
            return false;
        }

        return true;
    }

    void PRender::Shutdown()
    {
        m_renderData = nullptr;
        m_internalRender = nullptr;
    }

    bool PRender::RenderFrame(RenderData *rData)
    {
        if (m_renderData == nullptr)
        {
            Picasso::Logger::Logger::Warn("Trying to call RenderFrame() method of PRender class without proper Init() before...ignoring and quitting");
            return true;
        }

        // start rendering the frame...
        if (!m_internalRender->BeginFrame(m_renderData, rData->deltaTime))
        {
            Picasso::Logger::Logger::Error("Unable to start rendering the frame...");
            return false;
        }

        //...and end it
        if (!m_internalRender->EndFrame(m_renderData, rData->deltaTime))
        {
            Picasso::Logger::Logger::Error("Unable to finish rendering the frame...");
            return false;
        }

        return true;
    }
}