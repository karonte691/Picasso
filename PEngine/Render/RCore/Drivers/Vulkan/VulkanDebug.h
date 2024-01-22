#pragma once

#ifndef VULKAN_DEBUG_H
#define VULKAN_DEBUG_H

#include <PEngine/Logger/Logger.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDriverData.h>

#include <Vulkan/vulkan.h>
#if defined(_WIN32)
#include <Vulkan/vulkan_win32.h>
#elif defined(__linux__)
#include <xcb/xcb.h>
#include <Vulkan/vulkan_xcb.h>
#endif

namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
    class VulkanDebug
    {
    public:
        static std::vector<const char *> GetValidationLayerList();
        static void PrintDeviceWaitError(VkResult error);
    };
}

#endif