#pragma once

#ifndef VULKAN_SWAP_CHAIN_MANAGER_H
#define VULKAN_SWAP_CHAIN_MANAGER_H

#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDriverData.h>
#include <memory>

namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
    class VUlkanSwapChainManager
    {
    public:
        void Create(DriverContext *contex, u_int32_t width, u_int32_t height);
        void ReCreate(DriverContext *contex, u_int32_t width, u_int32_t height);
        void Destroy(DriverContext *contex);

    private:
        std::shared_ptr<VulkanSwapChain> m_swapChain;
        u_int32_t m_imageIndex;

        bool _fetchNextImageIndex(DriverContext *context, u_int64_t timeout, VkSemaphore imageSemaphore);
    };
}
#endif