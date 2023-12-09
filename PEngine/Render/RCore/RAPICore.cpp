#include <PEngine/Render/RCore/RAPICore.h>

namespace Picasso::Engine::Render::Core
{
    RAPICore::RAPICore()
    {
        m_driverManager = std::make_unique<DriverManager>();
    }

    bool RAPICore::Create(const char *appName, RDRIVERS driver, EngineState *pState, std::shared_ptr<RAPIData> rcData)
    {
        rcData->pState = pState;

        m_renderDriver = m_driverManager->GetDriver(driver);

        if (m_renderDriver == nullptr)
        {
            Picasso::Logger::Logger::Fatal("Render driver not supported");
            return false;
        }

        if (!m_renderDriver->InitDriver(rcData, appName, pState))
        {
            Picasso::Logger::Logger::Fatal("Unable to initialize the driver");
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