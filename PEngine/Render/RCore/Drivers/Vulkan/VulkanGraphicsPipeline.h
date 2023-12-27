#pragma once

#ifndef VULKAN_GRAPHICS_PIPELINE_H
#define VULKAN_GRAPHICS_PIPELINE_H

#include <memory>
#include <PEngine/PState.h>
#include <PEngine/Logger/Logger.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDriverData.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanRenderPass.h>

namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
    struct AttachmentReferences
    {
        VkAttachmentReference colorAttachmentReference;
        VkAttachmentReference depthAttachmentReference;
    };

    class VulkanGraphicsPipeline
    {
    public:
        VulkanRenderPass RenderPassCreate(DriverContext *context,
                                          VulkanRenderPassArea area,
                                          VulkanRenderPassColor color,
                                          _Float32 depth,
                                          u_int32_t stencil);
        void RenderPassDestroy(DriverContext *context, VulkanRenderPass *vRenderPassData);
        void RenderPassBegin(VulkanCommandBufferDto *vCmBuffer, VulkanRenderPass *vRenderPassData, VkFramebuffer frameBuffer);
        void RenderPassEnd(VulkanCommandBufferDto *vCmBuffer, VulkanRenderPass *vRenderPassData);

    private:
        std::vector<VkAttachmentDescription> _getAttachmentDescription(const DriverContext *context);
        AttachmentReferences _getAttachmentReferences();
        VkAttachmentDescription _getColorAttachmentDescription(const DriverContext *context);
        VkAttachmentDescription _getDepthAttachmentDescription(const DriverContext *context);
        VkSubpassDependency _getDependency();
        VkSubpassDescription _getSubpassDescription(VkAttachmentReference colorAttachmentReference, VkAttachmentReference depthAttachmentReference);
    };
}
#endif