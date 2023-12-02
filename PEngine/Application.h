#pragma once

#ifndef APPLICATION_H
#define APPLICATION_H

#include <PEngine/PConfig.h>
#include <PEngine/Logger.h>
#include <PEngine/EventSystem/PERegistry.h>
#include <PEngine/Platform/Platform.h>
#include <PEngine/Input/PInput.h>


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