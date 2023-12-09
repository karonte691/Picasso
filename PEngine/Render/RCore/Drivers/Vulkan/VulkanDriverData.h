#pragma once

#ifndef VULKAN_DRIVER_DATA_H
#define VULKAN_DRIVER_DATA_H

#include <Vulkan/vulkan.h>
#if defined(_WIN32)
#include <Vulkan/vulkan_win32.h>
#elif defined(__linux__)
#include <xcb/xcb.h>
#include <Vulkan/vulkan_xcb.h>
#endif

namespace Picasso::Engine::Render::Core::Drivers
{
    struct Devices
    {
        VkPhysicalDevice physicalDevice;
        VkDevice device;
    };

    struct DriverContext
    {
        VkInstance vulkanInstance = VK_NULL_HANDLE;
        VkSurfaceKHR surface = VK_NULL_HANDLE;
        Devices devices = {VK_NULL_HANDLE, VK_NULL_HANDLE};
    };
}
#endif