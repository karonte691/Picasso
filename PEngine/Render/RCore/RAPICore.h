#pragma once

#ifndef R_API_CORE_H
#define R_API_CORE_H

#include <memory>
#include <PEngine/Logger/Logger.h>
#include <PEngine/PState.h>
#include <PEngine/Render/RData.h>
#include <PEngine/Render/RCore/DriverManager.h>
#include <PEngine/Render/RCore/GraphicsPipelineFactory.h>
#include <PEngine/Render/RCore/Drivers/DriverImplementation.h>

namespace Picasso::Engine::Render::Core
{
    using Picasso::Engine::EngineState;
    using Picasso::Engine::Render::RAPIData;
    using Picasso::Engine::Render::Core::Drivers::DriverImplementation;

    class RAPICore
    {
    public:
        RAPICore();

        bool Create(const char *appName, RDRIVERS driver, PPlatformState *pState, EngineState *eState, RAPIData *rcData);
        void Destroy();
        void Resize(RAPIData *apiData, uint16_t width, u_int16_t height);
        bool BeginFrame(RAPIData *apiData, float deltaTime, PPlatformState *pState);
        bool EndFrame(RAPIData *apiData, float deltaTime, PPlatformState *pState);

    private:
        std::unique_ptr<DriverImplementation> m_renderDriver;
        std::unique_ptr<DriverManager> m_driverManager;
        std::unique_ptr<RGraphicsPipeline> p_GraphicsPipeline;
    };
}

#endif