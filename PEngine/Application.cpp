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

        delete m_input;
        m_input = nullptr;

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
   
        engineState->running = true;
        engineState->suspended = false;

        return true;
    }

    bool Application::Run()
    {
        while (engineState->running)
        {
            if(engineState->suspended)
            {
                //we should not continue the processing 
                engineState->running = false;
                continue;
            }

            if(!m_platform->Process())
            {
                //quitting event
                engineState->running = false;   
                continue;         
            }

            m_input->Update(0);
        }

        Picasso::Logger::Logger::Debug("Shutting down Input system");
        m_input->Shutdown();

        Picasso::Logger::Logger::Debug("Shutting down Platform layer");
        m_platform->Shutdown();    
        
        return true;  
    }
}