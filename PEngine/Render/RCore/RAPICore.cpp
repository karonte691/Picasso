#include <PEngine/Render/RCore/RAPICore.h>

namespace Picasso::Engine::Render::Core
{
    RAPICore::RAPICore()
    {
        m_driverManager = std::make_unique<DriverManager>();
    }

    bool RAPICore::Create(const char* appName, RDRIVERS driver, EngineState* pState, std::shared_ptr<RAPIData> rcData)
    {
        rcData->pState = pState;

        m_renderDriver = m_driverManager->GetDriver(driver);

        if(m_renderDriver == nullptr)
        {
            Picasso::Logger::Logger::Fatal("Render driver not supported");
            return false;
        }

        
        return true;
    }
}