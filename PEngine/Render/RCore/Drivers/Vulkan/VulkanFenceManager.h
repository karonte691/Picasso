#pragma once

#ifndef VULKAN_FENCE_MANAGER_H
#define VULKAN_FENCE_MANAGER_H

#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDriverData.h>

namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
    class VulkanFenceManager
    {
    public:
        std::shared_ptr<VulkanFence> Create(DriverContext *context, bool isSignaled);
        bool Reset(DriverContext *context, std::shared_ptr<VulkanFence> vFence);
        void Destroy(DriverContext *context, std::shared_ptr<VulkanFence> vFence);
        bool Wait(DriverContext *context, std::shared_ptr<VulkanFence> vFence, u_int64_t timeout);
    };
}

#endif