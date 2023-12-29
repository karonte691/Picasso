#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanGraphicsPipeline.h>

#include <vector>

namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
    VulkanRenderPass VulkanGraphicsPipeline::RenderPassCreate(DriverContext *context,
                                                              VulkanRenderPassArea area,
                                                              VulkanRenderPassColor color,
                                                              _Float32 depth,
                                                              u_int32_t stencil)
    {
        if (!context || !context->devices.logicalDevice)
        {
            Picasso::Engine::Logger::Logger::Error("Context o Logical Device not valid");
            return {};
        }

        VulkanRenderPass rpData;

        std::vector<VkAttachmentDescription> attachDescription = this->_getAttachmentDescription(context);
        AttachmentReferences attachmentRefs = this->_getAttachmentReferences();

        VkSubpassDescription subPassDescrion = this->_getSubpassDescription(attachmentRefs.colorAttachmentReference, attachmentRefs.depthAttachmentReference);
        VkSubpassDependency dependency = this->_getDependency();

        VkRenderPassCreateInfo renderPassCreateInfo = {};
        renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassCreateInfo.attachmentCount = static_cast<uint32_t>(attachDescription.size());
        renderPassCreateInfo.pAttachments = attachDescription.data();
        renderPassCreateInfo.subpassCount = 1;
        renderPassCreateInfo.pSubpasses = &subPassDescrion;
        renderPassCreateInfo.dependencyCount = 1;
        renderPassCreateInfo.pDependencies = &dependency;

        VkRenderPass renderPass;
        VkResult createRenderPassRes = vkCreateRenderPass(context->devices.logicalDevice, &renderPassCreateInfo, nullptr, &renderPass);

        if (createRenderPassRes != VK_SUCCESS)
        {
            Picasso::Engine::Logger::Logger::Error("Impossibile creare il render pass");
            return {};
        }

        rpData.renderHandler = std::make_shared<VkRenderPass>(renderPass);

        return rpData;
    }

    void VulkanGraphicsPipeline::RenderPassDestroy(DriverContext *context, VulkanRenderPass *vRenderPassData)
    {
        if (vRenderPassData == nullptr || vRenderPassData->renderHandler == VK_NULL_HANDLE)
        {
            return;
        }

        vkDestroyRenderPass(context->devices.logicalDevice, *vRenderPassData->renderHandler, 0);

        vRenderPassData->renderHandler = VK_NULL_HANDLE;
    }

    void VulkanGraphicsPipeline::RenderPassBegin(VulkanCommandBufferDto *vCmBuffer, VulkanRenderPass *vRenderPassData, VkFramebuffer frameBuffer)
    {
        VkClearValue clearValues[2];
        VkRenderPassBeginInfo rpBeginInfo = {VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO};

        rpBeginInfo.renderPass = *vRenderPassData->renderHandler;
        rpBeginInfo.framebuffer = frameBuffer;
        rpBeginInfo.renderArea.offset.x = vRenderPassData->area.x;
        rpBeginInfo.renderArea.offset.y = vRenderPassData->area.y;
        rpBeginInfo.renderArea.extent.width = vRenderPassData->area.w;
        rpBeginInfo.renderArea.extent.height = vRenderPassData->area.h;

        clearValues[0].color.float32[0] = vRenderPassData->color.r;
        clearValues[0].color.float32[1] = vRenderPassData->color.g;
        clearValues[0].color.float32[2] = vRenderPassData->color.b;
        clearValues[0].color.float32[3] = vRenderPassData->color.a;

        clearValues[1].depthStencil.depth = vRenderPassData->depth;
        clearValues[1].depthStencil.stencil = vRenderPassData->stencil;

        rpBeginInfo.clearValueCount = 2;
        rpBeginInfo.pClearValues = clearValues;

        vkCmdBeginRenderPass(*vCmBuffer->commandBufferHandler.get(), &rpBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

        vCmBuffer->state = COMMAND_BUFFER_STATE_IN_RENDER_PASS;
    }

    void VulkanGraphicsPipeline::RenderPassEnd(VulkanCommandBufferDto *vCmBuffer, VulkanRenderPass *vRenderPassData)
    {
        vkCmdEndRenderPass(*vCmBuffer->commandBufferHandler.get());
        vCmBuffer->state = COMMAND_BUFFER_STATE_RECORDING;
    }

    std::vector<VkAttachmentDescription> VulkanGraphicsPipeline::_getAttachmentDescription(const DriverContext *context)
    {
        u_int32_t attachmentDescrCount = 2;
        std::vector<VkAttachmentDescription> attachDescription(attachmentDescrCount);

        attachDescription[0] = this->_getColorAttachmentDescription(context);
        attachDescription[1] = this->_getDepthAttachmentDescription(context);

        return attachDescription;
    }

    AttachmentReferences VulkanGraphicsPipeline::_getAttachmentReferences()
    {
        VkAttachmentReference colorAttachmentReference;
        VkAttachmentReference depthAttachmentReference;

        colorAttachmentReference.attachment = 0;
        depthAttachmentReference.attachment = 0;

        colorAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        depthAttachmentReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        AttachmentReferences refs;

        refs.colorAttachmentReference = colorAttachmentReference;
        refs.depthAttachmentReference = depthAttachmentReference;

        return refs;
    }

    VkAttachmentDescription VulkanGraphicsPipeline::_getColorAttachmentDescription(const DriverContext *context)
    {
        VkAttachmentDescription colorAttachment;
        colorAttachment.format = context->swapChain->imageFormat.format;
        colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
        colorAttachment.flags = 0;

        return colorAttachment;
    }

    VkAttachmentDescription VulkanGraphicsPipeline::_getDepthAttachmentDescription(const DriverContext *context)
    {
        VkAttachmentDescription depthAttachment;

        depthAttachment.format = context->devices.depthFormat;
        depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        return depthAttachment;
    }

    VkSubpassDependency VulkanGraphicsPipeline::_getDependency()
    {
        VkSubpassDependency dependency;

        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;
        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.srcAccessMask = 0;
        dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        dependency.dependencyFlags = 0;

        return dependency;
    }

    VkSubpassDescription VulkanGraphicsPipeline::_getSubpassDescription(VkAttachmentReference colorAttachmentReference, VkAttachmentReference depthAttachmentReference)
    {
        VkSubpassDescription subpassDescrion;

        subpassDescrion.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpassDescrion.colorAttachmentCount = 1;
        subpassDescrion.pColorAttachments = &colorAttachmentReference;
        subpassDescrion.pDepthStencilAttachment = &depthAttachmentReference;
        subpassDescrion.inputAttachmentCount = 0;
        subpassDescrion.pInputAttachments = 0;
        subpassDescrion.pResolveAttachments = 0;
        subpassDescrion.preserveAttachmentCount = 0;
        subpassDescrion.pPreserveAttachments = 0;

        return subpassDescrion;
    }
}