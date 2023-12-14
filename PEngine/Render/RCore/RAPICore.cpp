#include <PEngine/Render/RCore/RAPICore.h>

namespace Picasso::Engine::Render::Core
{
    RAPICore::RAPICore()
    {
        m_driverManager = std::make_unique<DriverManager>();
    }

    bool RAPICore::Create(const char *appName, RDRIVERS driver, std::shared_ptr<PPlatformState> pState, EngineState *eState, std::shared_ptr<RAPIData> rcData)
    {
        rcData->pState = eState;

        m_renderDriver = m_driverManager->GetDriver(driver);

        if (m_renderDriver == nullptr)
        {
            Picasso::Engine::Logger::Logger::Fatal("Render driver not supported");
            return false;
        }

        if (!m_renderDriver->InitDriver(rcData, appName, pState, eState))
        {
            Picasso::Engine::Logger::Logger::Fatal("Unable to initialize the driver");
            m_renderDriver->Shutdown();
            return false;
        }

        return true;
    }

    void RAPICore::Destroy()
    {
        m_renderDriver->Shutdown();
    }

    void RAPICore::Resize(std::shared_ptr<RAPIData> apiData, uint16_t width, u_int16_t height)
    {
    }

    bool RAPICore::BeginFrame(std::shared_ptr<RAPIData> apiData, _Float32 deltaTime)
    {
        return true;
    }

    bool RAPICore::EndFrame(std::shared_ptr<RAPIData> apiData, _Float32 deltaTime)
    {
        return true;
    }

}