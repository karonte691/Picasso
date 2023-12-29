#pragma once

#ifndef VULKAN_FRAME_BUFFER
#define VULKAN_FRAME_BUFFER

#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDriverData.h>

namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
    class VulkanFrameBuffer
    {
    public:
        std::shared_ptr<VulkanFrameBufferDto> DecorateContext(DriverContext *context,
                                                              std::shared_ptr<VulkanRenderPass> renderPass,
                                                              u_int32_t width,
                                                              u_int32_t height,
                                                              u_int32_t attachmentCount,
                                                              VkImageView attachments[]);
        void Clear(DriverContext *context, std::shared_ptr<VulkanFrameBufferDto> frameBuffer);
    };
}

#endif