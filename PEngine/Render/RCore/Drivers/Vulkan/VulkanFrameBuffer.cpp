#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanFrameBuffer.h>

namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
    std::shared_ptr<VulkanFrameBufferDto> VulkanFrameBuffer::DecorateContext(DriverContext *context,
                                                                             std::shared_ptr<VulkanRenderPass> renderPass,
                                                                             u_int32_t width,
                                                                             u_int32_t height,
                                                                             u_int32_t attachmentCount,
                                                                             VkImageView attachments[])
    {
        std::shared_ptr<VulkanFrameBufferDto> frameBuffer = std::make_shared<VulkanFrameBufferDto>();

        frameBuffer->attachments.resize(attachmentCount);

        for (u_int32_t i = 0; i < attachmentCount; ++i)
        {
            frameBuffer->attachments[i] = attachments[i];
        }
        frameBuffer->renderPass = renderPass;
        frameBuffer->attachmentCount = attachmentCount;

        VkFramebufferCreateInfo fbCreateInfo = {VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO};

        fbCreateInfo.renderPass = *renderPass->renderHandler;
        fbCreateInfo.attachmentCount = attachmentCount;
        fbCreateInfo.pAttachments = frameBuffer->attachments.data();
        fbCreateInfo.width = width;
        fbCreateInfo.height = height;
        fbCreateInfo.layers = 1;

        VkResult frameBufferCreatedRes = vkCreateFramebuffer(context->devices.logicalDevice, &fbCreateInfo, 0, &frameBuffer->handler);

        if (frameBufferCreatedRes != VK_SUCCESS)
        {
            Picasso::Engine::Logger::Logger::Error("Could not create frame buffer");
            return nullptr;
        }

        return frameBuffer;
    }

    void VulkanFrameBuffer::Clear(DriverContext *context, std::shared_ptr<VulkanFrameBufferDto> frameBuffer)
    {
        if (context != nullptr && frameBuffer->handler)
        {
            vkDestroyFramebuffer(context->devices.logicalDevice, frameBuffer->handler, 0);
            frameBuffer->attachments.clear();
        }

        frameBuffer->handler = nullptr;
        frameBuffer->attachmentCount = 0;
        frameBuffer->renderPass = nullptr;
    }
}