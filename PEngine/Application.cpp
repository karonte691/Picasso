#include <PEngine/Application.h>

#include <chrono>
#include <thread>

namespace Picasso::Engine
{
    Picasso::Engine::EngineState *Picasso::Engine::Application::engineState;

    Application::Application()
    {
        if (engineState != nullptr)
        {
            return;
        }

        engineState = new EngineState{false, false, 800, 600, 0.0, 0.0, 0.0f};

        // init event system
        PicassoRegistry::Init();
    }

    Application::~Application()
    {
        if (engineState != nullptr)
        {
            delete engineState;
            engineState = nullptr;
        }

        delete m_platform;
        m_platform = nullptr;

        delete m_input;
        m_input = nullptr;

        delete m_internalClock;
        m_internalClock = nullptr;

        delete m_time;
        m_time = nullptr;

        PicassoRegistry::Reset();
    }

    bool Application::Create(Picasso::Config::AppConfig *config)
    {
        // avoid running multiple instance
        if (engineState->running == true)
        {
            Picasso::Logger::Logger::Fatal("An instance of PicassoEngine is already running");
            return false;
        }

        Picasso::Logger::Logger::Info("Platform layer startup...");

        m_platform = new PPlatform();

        bool platformInitResult = m_platform->Init(
            config->appName,
            config->startPositionX,
            config->startPositionY,
            config->startWidth,
            config->startHeight);

        if (!platformInitResult)
        {
            Picasso::Logger::Logger::Fatal("Error while loading platform layer");
            return false;
        }

        Picasso::Logger::Logger::Info("Input layer startup...");

        m_input = new PInput();
        m_input->Init();

        // render system
        Picasso::Logger::Logger::Info("Render layer startup...");
        m_render = new PRender();
        m_render->Init(config->appName, engineState);

        // setting up the internal clock
        m_internalClock = new Clock();
        m_time = new PTime();

        engineState->running = true;
        engineState->suspended = false;

        return true;
    }

    bool Application::Run()
    {
        while (engineState->running)
        {
            this->_Paint();
        }

        Picasso::Logger::Logger::Debug("Shutting down Internal clock");
        m_internalClock->Stop(engineState->clockData);

        Picasso::Logger::Logger::Debug("Shutting down Input system");
        m_input->Shutdown();

        Picasso::Logger::Logger::Debug("Shutting down Platform layer");
        m_platform->Shutdown();

        return true;
    }

    void Application::_Paint()
    {
        m_time->StartDeltaTime();

        if (engineState->suspended)
        {
            // we should not continue the processing
            engineState->running = false;
            return;
        }

        if (!m_platform->Process())
        {
            // quitting event
            engineState->running = false;
            return;
        }

        m_time->EndDeltaTime();
        float rawDeltaTime = m_time->GetRawDeltaTime();

        if (rawDeltaTime < PICASSO_FRAME_MS_LIMIT)
        {
            std::this_thread::sleep_for(m_time->GetSleepTime());
        }

        float deltaTime = m_time->GetDeltaTime();

        Picasso::Logger::Logger::FDebug("Delta time: %f", deltaTime);

        m_input->Update(deltaTime);
    }
}