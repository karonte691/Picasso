#pragma once

#ifndef VULKAN_DEVICE_H
#define VULKAN_DEVICE_H

#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDriverData.h>

namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
    class VulkanDevice
    {
    public:
        bool Create(DriverContext context);
        void Destroy();
    };
}

#endif