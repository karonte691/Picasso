#include <PEngine/Render/PRender.h>

namespace Picasso::Engine::Render
{
    using Picasso::Engine::Render::Core::RDRIVERS;

    bool PRender::Init(const char *appName, std::shared_ptr<PPlatformState> pState, EngineState *engineState)
    {
        if (m_renderData != nullptr)
        {
            Picasso::Engine::Logger::Logger::Warn("Trying to call Init() method of PRender class again...ignoring and quitting");
            return true;
        }

        m_internalRender = std::make_unique<RAPICore>();
        m_renderData = std::make_shared<RAPIData>();

        if (!m_internalRender->Create(appName, RDRIVERS::VULKAN, pState, engineState, m_renderData))
        {
            Picasso::Engine::Logger::Logger::Fatal("Error trying to setup the internal render...");
            return false;
        }

        return true;
    }

    void PRender::Shutdown()
    {
        m_renderData = nullptr;

        m_internalRender->Destroy();

        m_internalRender = nullptr;
    }

    bool PRender::RenderFrame(RenderData *rData, std::shared_ptr<PPlatformState> pState)
    {
        if (m_renderData == nullptr)
        {
            Picasso::Engine::Logger::Logger::Warn("Trying to call RenderFrame() method of PRender class without proper Init() before...ignoring and quitting");
            return true;
        }

        // rendering the frame...
        if (m_internalRender->BeginFrame(m_renderData, rData->deltaTime, pState))
        {
            if (!m_internalRender->EndFrame(m_renderData, rData->deltaTime))
            {
                Picasso::Engine::Logger::Logger::Error("Unable to rendering the frame...");
                return false;
            }

            m_renderData->frameNumber++;
            Picasso::Engine::Logger::Logger::Debug("Render completed succesfully");
        }

        return true;
    }
}