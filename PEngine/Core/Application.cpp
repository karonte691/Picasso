#include <PEngine/Core/Application.h>

#include <chrono>
#include <thread>
#include <iostream>
namespace Picasso::Engine::Core
{
    Picasso::Engine::EngineState *Picasso::Engine::Core::Application::engineState;

    Application::Application()
    {
        if (engineState != nullptr)
        {
            return;
        }

        engineState = new EngineState{false, false, 800, 600, 0.0, 0.0, 0.0f};

        // init event system
        PicassoRegistry::Init();

        // init file manager
        FileManager::Instance = new FileManager();
    }

    Application::~Application()
    {
        Picasso::Engine::EventSystem::PicassoRegistry::Unsubscribe(this, PEvent::RESIZED);

        if (engineState != nullptr)
        {
            delete engineState;
            engineState = nullptr;
        }

        PicassoRegistry::Reset();

        delete FileManager::Instance;
        FileManager::Instance = nullptr;
    }

    bool Application::Create(Picasso::Config::AppConfig *config)
    {
        // avoid running multiple instance
        if (engineState->running == true)
        {
            Picasso::Engine::Logger::Logger::Fatal("An instance of PicassoEngine is already running");
            return false;
        }

        Picasso::Engine::Logger::Logger::Info("Picasso Engine version %d.%d", PICASSO_MAJOR_VERSION, PICASSO_MINOR_VERSION);
        Picasso::Engine::Logger::Logger::Info("Patch version %d", PICASSO_PATCH_VERSION);

        FileManager::Instance->Init();

        Picasso::Engine::Logger::Logger::Info("Platform layer startup...");
        p_Platform = std::make_unique<PPlatform>();

        bool platformInitResult = p_Platform->Init(
            config->appName,
            config->startPositionX,
            config->startPositionY,
            config->startWidth,
            config->startHeight);

        if (!platformInitResult)
        {
            Picasso::Engine::Logger::Logger::Fatal("Error while loading platform layer");
            return false;
        }

        p_PlatformState = p_Platform->GetState();

        Picasso::Engine::Logger::Logger::Info("Input layer startup...");

        p_Input = std::make_unique<PInput>();
        p_Input->Init();

        Picasso::Engine::Logger::Logger::Info("Controller system startup...");
        p_ControllerSystem = std::make_unique<ControllerSystem>();

        if (!p_ControllerSystem->LoadControllers())
        {
            Picasso::Engine::Logger::Logger::Fatal("Unable to load controllers");
            return false;
        }

        // render system
        Picasso::Engine::Logger::Logger::Info("Render layer startup...");
        p_Render = std::make_unique<PRender>();

        if (!p_Render->Init(config->appName, p_PlatformState.get(), engineState))
        {
            Picasso::Engine::Logger::Logger::Fatal("Unable to start render layer...");
            return false;
        }

        p_FrameData = std::make_unique<RenderData>();

        // setting up the internal clock
        p_InternalClock = std::make_unique<Clock>();
        p_Time = std::make_unique<PTime>();

        engineState->running = true;
        engineState->suspended = false;

        // setting up listener to the resize event
        PicassoRegistry::Subscribe(this, PEvent::RESIZED, [this](BaseEvent<PEvent> *&event)
                                   { this->_OnResize(event); });

        return true;
    }

    bool Application::Run()
    {
        while (engineState->running)
        {
            this->_Paint();
        }

        Picasso::Engine::Logger::Logger::Debug("Shutting down Internal clock");
        p_InternalClock->Stop(engineState->clockData);

        Picasso::Engine::Logger::Logger::Debug("Shutting down Input system");
        p_Input->Shutdown();

        Picasso::Engine::Logger::Logger::Debug("Shutting down Rendering system");
        p_Render->Shutdown();

        Picasso::Engine::Logger::Logger::Debug("Shutting down Platform layer");
        p_Platform->Shutdown();

        return true;
    }

    void Application::_Paint()
    {
        p_Time->StartDeltaTime();

        if (engineState->suspended)
        {
            // we should not continue the processing
            engineState->running = false;
            return;
        }

        if (!p_Platform->Process())
        {
            // quitting event
            engineState->running = false;
            return;
        }

        p_Time->EndDeltaTime();
        float rawDeltaTime = p_Time->GetRawDeltaTime();

        if (rawDeltaTime < PICASSO_FRAME_MS_LIMIT)
        {
            std::this_thread::sleep_for(p_Time->GetSleepTime());
        }

        p_FrameData->deltaTime = p_Time->GetDeltaTime();
        // Picasso::Engine::Logger::Logger::Debug("Delta time: %f", m_frameData->deltaTime);

        // controllers update
        p_ControllerSystem->UpdateControllers();

        if (!p_Render->RenderFrame(p_FrameData.get(), p_Platform->GetState().get()))
        {
            // not a critical error ONE corrupted frame..but..
            engineState->running = false;
            return;
        }
    }

    void Application::_OnResize(BaseEvent<PEvent> *&event)
    {
        Picasso::Engine::Logger::Logger::Debug("Received resize event");

        EventSystem::Events::PEventData eventData = event->GetData();

        u_int16_t width = eventData.data.u16[0];
        u_int16_t height = eventData.data.u16[1];

        Picasso::Engine::Logger::Logger::Debug("New width %d, new height %d", width, height);

        p_Render->OnResize(width, height);
    }
}