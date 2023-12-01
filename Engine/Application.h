#pragma once

#ifndef APPLICATION_H
#define APPLICATION_H

#include <Engine/PConfig.h>
#include <Engine/Logger.h>
#include <Engine/EventSystem/PERegistry.h>
#include <Engine/Platform/Platform.h>
#include <Engine/Input/PInput.h>


namespace Picasso::Engine
{
    using Picasso::Engine::EventSystem::Events::BaseEvent;
    using Picasso::Engine::EventSystem::Events::PEvent;
    using Picasso::Engine::EventSystem::PicassoRegistry;
    using Picasso::Engine::Platform::PPlatform;
    using Picasso::Engine::Input::PInput;

    struct EngineState
    {
        bool running;
        bool suspended;
        int width;
        int height;
        float lastTime;
    };
    
    class Application
    {
    public:
        Application();
        ~Application();

        bool Create(Picasso::Config::AppConfig* config);
        bool Run();

        static Picasso::Engine::EngineState* engineState;
    private:
        PPlatform* m_platform;
        PInput* m_input;
    };
}

#endif