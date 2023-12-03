#pragma once

#ifndef R_CORE_H
#define R_CORE_H

#include <memory>
#include <PEngine/Logger.h>
#include <PEngine/Render/RData.h>
#include <PEngine/Render/RCore/DriverManager.h>
#include <PEngine/Render/RCore/Drivers/DriverImplementation.h>


namespace Picasso::Engine::Render::Core
{
    struct rCoreData
    {
        platformState* pState;
    };

    using Picasso::Engine::Render::Core::Drivers::DriverImplementation;

    class RCore
    {
        public:          
            RCore();

            bool Create(RDRIVERS driver, platformState* pState, rCoreData* rcData);
            void Destroy(rCoreData* rcData);

        private:
            std::shared_ptr<DriverImplementation> m_renderDriver;
            std::unique_ptr<DriverManager> m_driverManager;
    };
}

#endif