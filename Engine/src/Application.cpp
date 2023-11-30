#include "Application.h"

namespace Picasso::Engine
{
    Picasso::Engine::EngineState* Picasso::Engine::Application::engineState;

    Application::Application()
    {
        if(engineState != nullptr)
        {
            return;
        }

        engineState = new EngineState{false, false, 0, 0, 0};
        
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

        m_platform = new Picasso::Engine::Platform::PPlatform();

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
   
        engineState->running = true;
        engineState->suspended = false;

        return true;
    }

    bool Application::Run()
    {
        while (engineState->running)
        {
            if(!m_platform->Process())
            {
                //quitting event
                break;
            }
        }

        Picasso::Logger::Logger::Debug("Shutting down Platform layer");

        m_platform->Shutdown();    
        
        return true;  
    }
}