#pragma once

#ifndef VULKAN_PLATFORM_H
#define VULKAN_PLATFORM_H

#include <memory>
#include <vector>

namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
    class VulkanPlatform
    {
    public:
        std::vector<const char *> GetPlatformExtensions();
    };
}

#endif
