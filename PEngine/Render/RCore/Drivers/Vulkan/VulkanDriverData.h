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

#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanRenderPass.h>

namespace Picasso::Engine::Render::Core::Drivers
{
    using Vulkan::VulkanCommandBufferDto;
    using Vulkan::VulkanFrameBufferDto;
    using Vulkan::VulkanRenderPass;

    struct SwapChainSupportInfo
    {
        VkSurfaceCapabilitiesKHR capabilities;
        uint32_t formatCount;
        std::shared_ptr<VkSurfaceFormatKHR[]> formats;
        uint32_t presentModeCount;
        std::shared_ptr<VkPresentModeKHR[]> presentMode;
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

    struct VulkanImage
    {
        VkImage imageHandler;
        VkDeviceMemory deviceMemory;
        VkImageView imageView;
        u_int32_t width;
        u_int32_t height;
    };

    struct VulkanSwapChain
    {
        VkSurfaceFormatKHR imageFormat;
        u_int8_t maxRenderFrames;
        VkSwapchainKHR scHandler;
        u_int32_t imageCount;
        std::unique_ptr<VkImage[]> images;
        std::unique_ptr<VkImageView[]> imageViews;
        std::shared_ptr<VulkanImage> vImage;
        std::vector<std::shared_ptr<VulkanFrameBufferDto>> frameBuffers;
    };

    struct DriverContext
    {
        VkInstance vulkanInstance = VK_NULL_HANDLE;
        VkSurfaceKHR surface = VK_NULL_HANDLE;
        Devices devices;
        u_int32_t frameBufferWidth = 0;
        u_int32_t frameBufferHeight = 0;
        std::shared_ptr<VulkanSwapChain> swapChain;
        std::vector<std::shared_ptr<VulkanCommandBufferDto>> *cmBuffers;
        VkCommandPool pool;
        std::shared_ptr<VulkanRenderPass> renderPass;
        u_int32_t imageIndex = 0;
        u_int32_t currentFrame = 0;
        bool recreateSwapChain = false;
        u_int32_t memoryIndex = -1;
    };

    struct VulkanImageCreateOptions
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

        VulkanImageCreateOptions()
            : imageType(VK_IMAGE_TYPE_2D), // un valore di default ragionevole
              width(0),
              height(0),
              imageFormat(VK_FORMAT_UNDEFINED),     // equivalente a "null" per VkFormat
              imageTiling(VK_IMAGE_TILING_OPTIMAL), // un valore di default ragionevole
              imageUsageflags(0),                   // nessun flag di utilizzo
              memoryFlags(0),                       // nessun flag di memoria
              createView(false),
              imageAspectFlags(0) // nessun flag di aspetto
        {
        }
    };
}
#endif