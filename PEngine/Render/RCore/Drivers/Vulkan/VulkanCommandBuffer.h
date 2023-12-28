#pragma once

#ifndef VULKAN_COMMAND_BUFFER
#define VULKAN_COMMAND_BUFFER

#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDriverData.h>

namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
    class VulkanCommandBuffer
    {
    public:
        bool DecorateContext(DriverContext *context, u_int32_t swapChainImageCount);
        void Clear(DriverContext *context);

        std::shared_ptr<VulkanCommandBufferDto> Allocate(const DriverContext *context, const VkCommandPool pool, const bool isPrimary);
        void Free(const DriverContext *context, VkCommandPool pool, std::shared_ptr<VulkanCommandBufferDto> cmBuffer);
        bool BeginRecording(std::shared_ptr<VulkanCommandBufferDto> cmBuffer, bool isSingleUse, bool isRenderPassContinue, bool isSimultaneos);
        bool EndRecording(std::shared_ptr<VulkanCommandBufferDto> cmBuffer);
        void Submitted(std::shared_ptr<VulkanCommandBufferDto> cmBuffer);
        void Reset(std::shared_ptr<VulkanCommandBufferDto> cmBuffer);

        // shortcut
        std::shared_ptr<VulkanCommandBufferDto> BuildSingleUse(DriverContext *context, VkCommandPool pool);
        bool EndSingleUse(DriverContext *context, VkCommandPool pool, std::shared_ptr<VulkanCommandBufferDto> cmBuffer, VkQueue queue);

    private:
        bool _createCommandPool(DriverContext *context);
    };
}
#endif