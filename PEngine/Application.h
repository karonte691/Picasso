#pragma once

#ifndef APPLICATION_H
#define APPLICATION_H

#include <PEngine/PConfig.h>
#include <PEngine/PState.h>
#include <PEngine/Logger.h>
#include <PEngine/Core/Clock.h>
#include <PEngine/EventSystem/PERegistry.h>
#include <PEngine/Platform/Platform.h>
#include <PEngine/Render/PRender.h>
#include <PEngine/Input/PInput.h>


namespace Picasso::Engine
{
    using Picasso::Engine::EventSystem::Events::BaseEvent;
    using Picasso::Engine::EventSystem::Events::PEvent;
    using Picasso::Engine::EventSystem::PicassoRegistry;
    using Picasso::Engine::Platform::PPlatform;
    using Picasso::Engine::Render::PRender;
    using Picasso::Engine::Input::PInput;
    using Picasso::Engine::Core::Clock;
    using Picasso::Engine::Core::ClockData;

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
        PRender* m_render;
        Clock* m_internalClock;

        void _Paint(u_int8_t& frameCount);
    };
}

#endif