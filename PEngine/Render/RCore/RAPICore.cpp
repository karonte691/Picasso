#include <PEngine/Render/RCore/RAPICore.h>

namespace Picasso::Engine::Render::Core
{
    RAPICore::RAPICore()
    {
        m_driverManager = std::make_unique<DriverManager>();
    }

    bool RAPICore::Create(const char *appName, RDRIVERS driver, PPlatformState *pState, EngineState *eState, RAPIData *rcData)
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

        GraphicsPipelineFactory *graphicsPipelineFactory = new GraphicsPipelineFactory();

        RGraphicsPipeline *gPipeline = graphicsPipelineFactory->Get(m_renderDriver.get());

        delete graphicsPipelineFactory;

        if (gPipeline == nullptr)
        {
            Picasso::Engine::Logger::Logger::Fatal("Unable to fetch a suitable graphics pipeline");

            m_renderDriver->Shutdown();
            return false;
        }

        p_GraphicsPipeline.reset(gPipeline);

        return true;
    }

    void RAPICore::Destroy()
    {
        m_renderDriver->Shutdown();
    }

    void RAPICore::Resize(RAPIData *apiData, uint16_t width, u_int16_t height)
    {
        m_renderDriver->OnResize(width, height);
    }

    bool RAPICore::BeginFrame(RAPIData *apiData, float deltaTime, PPlatformState *pState)
    {
        return p_GraphicsPipeline->BeginFrame(apiData, deltaTime, pState);
    }

    bool RAPICore::EndFrame(RAPIData *apiData, float deltaTime, PPlatformState *pState)
    {
        return p_GraphicsPipeline->EndFrame(apiData, deltaTime, pState);
    }

}