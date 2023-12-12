#pragma once

#ifndef VULKAN_DRIVER_DATA_H
#define VULKAN_DRIVER_DATA_H

#include <memory>

#include <Vulkan/vulkan.h>
#if defined(_WIN32)
#include <Vulkan/vulkan_win32.h>
#elif defined(__linux__)
#include <xcb/xcb.h>
#include <Vulkan/vulkan_xcb.h>
#endif

namespace Picasso::Engine::Render::Core::Drivers
{
    struct SwapChainSupportInfo
    {
        VkSurfaceCapabilitiesKHR capabilities;
        uint32_t formatCount;
        std::unique_ptr<VkSurfaceFormatKHR[]> formats;
        uint32_t presentModeCount;
        std::unique_ptr<VkPresentModeKHR[]> presentMode;
    };

    struct Devices
    {
        VkPhysicalDevice physicalDevice;
        VkDevice logicalDevice;
        SwapChainSupportInfo swapChainSupport;
        u_int32_t graphicsQueueIndex;
        u_int32_t presentQueueIndex;
        u_int32_t transferQueueIndex;
        VkPhysicalDeviceProperties properties;
        VkPhysicalDeviceFeatures features;
        VkPhysicalDeviceMemoryProperties memoryProperties;
    };

    struct DriverContext
    {
        VkInstance vulkanInstance = VK_NULL_HANDLE;
        VkSurfaceKHR surface = VK_NULL_HANDLE;
        Devices devices;
    };
}
#endif