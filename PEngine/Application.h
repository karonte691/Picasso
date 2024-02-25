#pragma once

#ifndef APPLICATION_H
#define APPLICATION_H

#include <PEngine/PConfig.h>
#include <PEngine/PBuild.h>
#include <PEngine/PState.h>
#include <PEngine/File/FileManager.h>
#include <PEngine/Logger/Logger.h>
#include <PEngine/Core/Clock.h>
#include <PEngine/Core/PTime.h>
#include <PEngine/EventSystem/PERegistry.h>
#include <PEngine/Platform/Platform.h>
#include <PEngine/Render/PRender.h>
#include <PEngine/Render/RData.h>
#include <PEngine/Input/PInput.h>
#include <PEngine/Controller/ControllerSystem.h>

namespace Picasso::Engine
{
    using Picasso::Engine::Controller::ControllerSystem;
    using Picasso::Engine::Core::Clock;
    using Picasso::Engine::Core::ClockData;
    using Picasso::Engine::Core::PTime;
    using Picasso::Engine::EventSystem::PicassoRegistry;
    using Picasso::Engine::EventSystem::Events::BaseEvent;
    using Picasso::Engine::EventSystem::Events::PEvent;
    using Picasso::Engine::File::FileManager;
    using Picasso::Engine::Input::PInput;
    using Picasso::Engine::Platform::PPlatform;
    using Picasso::Engine::Render::PRender;
    using Picasso::Engine::Render::RenderData;

    class Application
    {
    public:
        Application();
        ~Application();

        bool Create(Picasso::Config::AppConfig *config);
        bool Run();

        static Picasso::Engine::EngineState *engineState;

    private:
        std::unique_ptr<PPlatform> p_Platform;
        std::unique_ptr<PInput> p_Input;
        std::unique_ptr<PRender> p_Render;
        std::unique_ptr<RenderData> p_FrameData;
        std::unique_ptr<Clock> p_InternalClock;
        std::shared_ptr<PPlatformState> p_PlatformState;
        std::unique_ptr<ControllerSystem> p_ControllerSystem;
        std::unique_ptr<PTime> p_Time;

        void _Paint();
        void _OnResize(BaseEvent<PEvent> *&event);
    };
}

#endif