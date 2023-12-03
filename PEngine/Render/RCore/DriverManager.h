#pragma once

#ifndef DRIVER_MANAGER_H
#define DRIVER_MANAGER_H

#include <memory>

#include <PEngine/Render/RCore/Drivers/DriverImplementation.h>

namespace Picasso::Engine::Render::Core
{
    enum RDRIVERS
    {
        VULKAN,
        //OPENGL NOT SUPPORTED
        //DIRECTX NOT SUPPORTED
    };

    using Picasso::Engine::Render::Core::Drivers::DriverImplementation;

    class DriverManager
    {
        public:
            std::shared_ptr<DriverImplementation> GetDriver(RDRIVERS driver);
    };
}

#endif