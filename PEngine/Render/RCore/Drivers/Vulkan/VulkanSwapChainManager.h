#pragma once

#ifndef VULKAN_SWAP_CHAIN_MANAGER_H
#define VULKAN_SWAP_CHAIN_MANAGER_H

#include <PEngine/Logger/Logger.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDriverData.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDevice.h>
#include <memory>

namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
    class VulkanSwapChainManager
    {
    public:
        void Create(DriverContext *contex, u_int32_t width, u_int32_t height, std::shared_ptr<VulkanDevice> m_device);
        void Destroy(DriverContext *contex);

    private:
        std::shared_ptr<VulkanSwapChain> m_swapChain;
        std::shared_ptr<u_int32_t> m_imageIndex;
        std::shared_ptr<VulkanDevice> m_device;

        void _createSwapChain(DriverContext *contex, u_int32_t width, u_int32_t height);
        void _reCreateSwapChain(DriverContext *contex, u_int32_t width, u_int32_t height);
        bool _fetchNextImageIndex(DriverContext *context, u_int64_t timeout, VkSemaphore imageSemaphore, VkFence fences);
        void _swapChainPresent(DriverContext *context, VkQueue graphicsQueue, VkQueue presentQueue, VkSemaphore renderComplete);
        void _calculateExtentDimension(DriverContext *context, VkExtent2D &extent);
        u_int32_t _getImageCount(DriverContext *context);
        VkSwapchainCreateInfoKHR *_getSwapChainCreateInfo(DriverContext *context, u_int32_t imageCount, VkExtent2D extent, VkPresentModeKHR presentMode);
    };
}
#endif