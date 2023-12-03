#include <PEngine/Application.h>

namespace Picasso::Engine
{
    Picasso::Engine::EngineState* Picasso::Engine::Application::engineState;

    Application::Application()
    {
        if(engineState != nullptr)
        {
            return;
        }

        engineState = new EngineState{false, false, 800, 600, 0.0, 0.0, 0.0f};
        
        //init event system
        PicassoRegistry::Init();
    }
    
    Application::~Application()
    {
        if(engineState != nullptr)
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

        PicassoRegistry::Reset();
    }

    bool Application::Create(Picasso::Config::AppConfig* config)
    {
        //avoid running multiple instance
        if(engineState->running == true)
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
                                        config->startHeight
                                  );

        if(!platformInitResult)
        {
            Picasso::Logger::Logger::Fatal("Error while loading platform layer");
            return false;
        }

        Picasso::Logger::Logger::Info("Input layer startup...");

        m_input = new PInput();
        m_input->Init();

        //render system
        Picasso::Logger::Logger::Info("Render layer startup...");
        m_render = new PRender();
        m_render->Init(config->appName, engineState);

        //setting up the internal clock
        m_internalClock = new Clock();
   
        engineState->running = true;
        engineState->suspended = false;

        return true;
    }

    bool Application::Run()
    {
        m_internalClock->Start(engineState->clockData, m_platform->GetAbsoluteTime());

        u_int8_t frameCount = 0;

        while (engineState->running)
        {
            this->_Paint(frameCount);
        }

        Picasso::Logger::Logger::Debug("Shutting down Internal clock");
        m_internalClock->Stop(engineState->clockData);

        Picasso::Logger::Logger::Debug("Shutting down Input system");
        m_input->Shutdown();

        Picasso::Logger::Logger::Debug("Shutting down Platform layer");
        m_platform->Shutdown();    
        

        return true;  
    }

    void Application::_Paint(u_int8_t& frameCount)
    {
        m_internalClock->Update(engineState->clockData, m_platform->GetAbsoluteTime());
        engineState->lastTime = engineState->clockData->elapsed;

        constexpr _Float64 target60Fps = 1.0f / 60;

        _Float64 currentTime = engineState->clockData->elapsed;
        _Float64 frameStartTime = m_platform->GetAbsoluteTime();

        if(engineState->suspended)
        {
            //we should not continue the processing 
            engineState->running = false;
            return;
        }

        if(!m_platform->Process())
        {
            //quitting event
            engineState->running = false;   
            return;         
        }

        _Float64 frameEndTime = m_platform->GetAbsoluteTime();
        _Float64 frameElapsedTime = frameEndTime - frameStartTime;
        _Float64 remainingSeconds = target60Fps - frameElapsedTime;
          
        if(remainingSeconds > 0)
        {
            _Float64 remainingMs = (remainingSeconds * 1000);

            if(remainingMs > 0 && PICASSO_RESTRAIN_FRAME_RATE) //PBBuild.h
            {
                m_platform->Suspend(remainingMs - 1);
            }

            frameCount++;
        }

        _Float64 deltaTime = (currentTime - engineState->lastTime);

        Picasso::Logger::Logger::FDebug("Delta time: %f", deltaTime);

        m_input->Update(deltaTime);

        engineState->lastTime = currentTime;
    }
}