#include <PEngine/Render/RCore/RCore.h>

namespace Picasso::Engine::Render::Core
{
    RCore::RCore()
    {
        m_driverManager = std::make_unique<DriverManager>();
    }

    bool RCore::Create(RDRIVERS driver, platformState* pState, rCoreData* rcData)
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