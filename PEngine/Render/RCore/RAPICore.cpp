/**
 * @file RAPICore.cpp
 * @brief Implementation of the RAPICore class.
 */
#include <PEngine/Render/RCore/RAPICore.h>

namespace Picasso::Engine::Render::Core
{
    /**
     * @brief Default constructor for the RAPICore class.
     */
    RAPICore::RAPICore()
    {
        m_driverManager = std::make_unique<DriverManager>();
    }

    /**
     * @brief Creates the RAPICore instance.
     * @param appName The name of the application.
     * @param driver The render driver to use.
     * @param pState Pointer to the platform state.
     * @param eState Pointer to the engine state.
     * @param rcData Pointer to the RAPIData.
     * @return True if creation is successful, false otherwise.
     */
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

        if (!gPipeline->Init(rcData))
        {
            Picasso::Engine::Logger::Logger::Fatal("Unable to init the graphics pipeline");

            m_renderDriver->Shutdown();
            return false;
        }

        gPipeline->RegisterHooks();

        p_GraphicsPipeline.reset(gPipeline);

        return true;
    }

    /**
     * @brief Destroys the RAPICore instance.
     */
    void RAPICore::Destroy()
    {
        p_GraphicsPipeline->Shutdown();
        m_renderDriver->Shutdown();
    }

    /**
     * @brief Resizes the rendering viewport.
     * @param apiData Pointer to the RAPIData.
     * @param width The new width of the viewport.
     * @param height The new height of the viewport.
     */
    void RAPICore::Resize(RAPIData *apiData, uint16_t width, u_int16_t height)
    {
        m_renderDriver->OnResize(width, height);
        p_GraphicsPipeline->Resize(width, height);
    }

    /**
     * @brief Begins a new frame.
     * @param apiData Pointer to the RAPIData.
     * @param deltaTime The time elapsed since the last frame.
     * @param pState Pointer to the platform state.
     * @return True if the frame begins successfully, false otherwise.
     */
    bool RAPICore::BeginFrame(RAPIData *apiData, float deltaTime, PPlatformState *pState)
    {
        return p_GraphicsPipeline->BeginFrame(apiData, deltaTime, pState);
    }

    /**
     * @brief Ends the current frame.
     * @param apiData Pointer to the RAPIData.
     * @param deltaTime The time elapsed since the last frame.
     * @param pState Pointer to the platform state.
     * @return True if the frame ends successfully, false otherwise.
     */
    bool RAPICore::EndFrame(RAPIData *apiData, float deltaTime, PPlatformState *pState)
    {
        return p_GraphicsPipeline->EndFrame(apiData, deltaTime, pState);
    }

}