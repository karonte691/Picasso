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
        VkQueue graphicsQueue;
        VkQueue presentQueue;
        VkQueue transferQueue;
        VkPhysicalDeviceProperties properties;
        VkPhysicalDeviceFeatures features;
        VkPhysicalDeviceMemoryProperties memoryProperties;
        VkFormat depthFormat = VK_FORMAT_UNDEFINED;
    };

    struct VulkanSwapChain
    {
        VkSurfaceFormatKHR imageFormat;
        u_int8_t maxRenderFrames;
        VkSwapchainKHR scHandler;
        u_int32_t imageCount;
        std::unique_ptr<VkImage[]> images;
        std::unique_ptr<VkImageView[]> imageViews;
    };

    struct VulkanImage
    {
        VkImage imageHandler;
        VkDeviceMemory deviceMemory;
        VkImageView imageView;
        u_int32_t width;
        u_int32_t height;
    };

    struct DriverContext
    {
        VkInstance vulkanInstance = VK_NULL_HANDLE;
        VkSurfaceKHR surface = VK_NULL_HANDLE;
        Devices devices;
        u_int32_t frameBufferWidth = 0;
        u_int32_t frameBufferHeight = 0;
        VulkanSwapChain swapChain;
        u_int32_t imageIndex = 0;
        u_int32_t currentFrame = 0;
        bool recreateSwapChain = false;
        u_int32_t memoryIndex = -1;
    };

    struct VulkanImageCreateInfo
    {
        VkImageType imageType;
        u_int32_t width;
        u_int32_t height;
        VkFormat imageFormat;
        VkImageTiling imageTiling;
        VkImageUsageFlags imageUsageflags;
        VkMemoryPropertyFlags memoryFlags;
        bool createView;
        VkImageAspectFlags imageAspectFlags;
    };
}
#endif