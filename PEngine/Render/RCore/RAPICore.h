#pragma once

#ifndef R_API_CORE_H
#define R_API_CORE_H

#include <memory>
#include <PEngine/Logger.h>
#include <PEngine/PState.h>
#include <PEngine/Render/RData.h>
#include <PEngine/Render/RCore/DriverManager.h>
#include <PEngine/Render/RCore/Drivers/DriverImplementation.h>


namespace Picasso::Engine::Render::Core
{
    using Picasso::Engine::Render::Core::Drivers::DriverImplementation;
    using Picasso::Engine::Render::RAPIData;
    using Picasso::Engine::EngineState;

    class RAPICore
    {
        public:          
            RAPICore();

            bool Create(const char* appName, RDRIVERS driver, EngineState* pState, std::shared_ptr<RAPIData> rcData);
            void Destroy(std::shared_ptr<RAPIData> rcData);
            void Resize(std::shared_ptr<RAPIData> apiData, uint16_t width, u_int16_t height);
            bool BeginFrame(std::shared_ptr<RAPIData> apiData, _Float32 deltaTime);
            bool EndFrame(std::shared_ptr<RAPIData> apiData, _Float32 deltaTime);

        private:
            std::shared_ptr<DriverImplementation> m_renderDriver;
            std::unique_ptr<DriverManager> m_driverManager;
    };
}

#endif