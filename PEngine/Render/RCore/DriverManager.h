#pragma once

#ifndef DRIVER_MANAGER_H
#define DRIVER_MANAGER_H

#include <memory>

#include <PEngine/Render/RCore/Drivers/DriverImplementation.h>

namespace Picasso::Engine::Render::Core
{

    using Picasso::Engine::Render::Core::Drivers::DriverImplementation;
    using Picasso::Engine::Render::Core::Drivers::RDRIVERS;

    class DriverManager
    {
    public:
        std::unique_ptr<DriverImplementation> GetDriver(RDRIVERS driver);
    };
}

#endif