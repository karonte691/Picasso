#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanCommandBuffer.h>

namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
    bool VulkanCommandBuffer::DecorateContext(DriverContext *context, u_int32_t swapChainImageCount)
    {
        if (swapChainImageCount == 0)
        {
            Picasso::Engine::Logger::Logger::Fatal("Command buffer: image count is zero");
            return false;
        }

        this->_createCommandPool(context);

        context->cmBuffers.resize(swapChainImageCount);

        for (u_int32_t i = 0; i < swapChainImageCount; ++i)
        {
            std::shared_ptr<VulkanCommandBufferDto> &buffer = context->cmBuffers[i];

            if (buffer && buffer->commandBufferHandler)
            {
                this->Free(context, context->pool, buffer);
            }

            buffer = this->Allocate(context, context->pool, true);

            context->cmBuffers[i] = buffer;
        }
        return true;
    }

    void VulkanCommandBuffer::Clear(DriverContext *context)
    {
        if (context->pool)
        {
            Picasso::Engine::Logger::Logger::Debug("Destroying command pool...");

            vkDestroyCommandPool(context->devices.logicalDevice, context->pool, 0);
        }
    }

    std::shared_ptr<VulkanCommandBufferDto> VulkanCommandBuffer::Allocate(const DriverContext *context, const VkCommandPool pool, const bool isPrimary)
    {
        std::shared_ptr<VulkanCommandBufferDto> cmBuffer = std::make_shared<VulkanCommandBufferDto>();
        cmBuffer->commandBufferHandler = std::make_shared<VkCommandBuffer>();

        VkCommandBufferAllocateInfo cmBufferAllocateInfo = {VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO};

        cmBufferAllocateInfo.commandPool = pool;
        cmBufferAllocateInfo.level = isPrimary ? VK_COMMAND_BUFFER_LEVEL_PRIMARY : VK_COMMAND_BUFFER_LEVEL_SECONDARY;
        cmBufferAllocateInfo.commandBufferCount = 1;
        cmBufferAllocateInfo.pNext = 0;

        cmBuffer->state = COMMAND_BUFFER_STATE_NOT_ALLOCATED;

        VkResult allocateCommandBufferRes = vkAllocateCommandBuffers(context->devices.logicalDevice, &cmBufferAllocateInfo, cmBuffer->commandBufferHandler.get());

        if (allocateCommandBufferRes != VK_SUCCESS)
        {
            Picasso::Engine::Logger::Logger::Error("Unable to allocate a command buffer");
            return nullptr;
        }

        cmBuffer->state = COMMAND_BUFFER_STATE_READY;

        return cmBuffer;
    }

    void VulkanCommandBuffer::Free(const DriverContext *context, VkCommandPool pool, std::shared_ptr<VulkanCommandBufferDto> cmBuffer)
    {
        if (cmBuffer->commandBufferHandler == nullptr || cmBuffer->commandBufferHandler == VK_NULL_HANDLE)
        {
            return;
        }

        vkFreeCommandBuffers(context->devices.logicalDevice, pool, 1, cmBuffer->commandBufferHandler.get());

        cmBuffer->commandBufferHandler = nullptr;
        cmBuffer->state = COMMAND_BUFFER_STATE_NOT_ALLOCATED;
    }

    void VulkanCommandBuffer::ConfigureViewPort(std::shared_ptr<VulkanCommandBufferDto> cmBuffer, VkViewport *vPort)
    {
        vkCmdSetViewport(*cmBuffer->commandBufferHandler, 0, 1, vPort);
    }

    void VulkanCommandBuffer::ConfigureScissor(std::shared_ptr<VulkanCommandBufferDto> cmBuffer, VkRect2D *scissor)
    {
        vkCmdSetScissor(*cmBuffer->commandBufferHandler, 0, 1, scissor);
    }

    bool VulkanCommandBuffer::BeginRecording(std::shared_ptr<VulkanCommandBufferDto> cmBuffer, bool isSingleUse, bool isRenderPassContinue, bool isSimultaneos)
    {
        VkCommandBufferBeginInfo aBeginInfo = {VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO};

        aBeginInfo.flags = 0;

        if (isSingleUse)
        {
            aBeginInfo.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        }

        if (isRenderPassContinue)
        {
            aBeginInfo.flags |= VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;
        }

        if (isSimultaneos)
        {
            aBeginInfo.flags |= VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
        }

        VkResult beginCommandBufferRes = vkBeginCommandBuffer(*cmBuffer->commandBufferHandler, &aBeginInfo);

        if (beginCommandBufferRes != VK_SUCCESS)
        {
            Picasso::Engine::Logger::Logger::Error("Unable to begin recording for a command buffer");
            return false;
        }

        cmBuffer->state = COMMAND_BUFFER_STATE_RECORDING;

        return true;
    }

    bool VulkanCommandBuffer::EndRecording(std::shared_ptr<VulkanCommandBufferDto> cmBuffer)
    {
        if (cmBuffer->commandBufferHandler == nullptr || cmBuffer->commandBufferHandler == VK_NULL_HANDLE)
        {
            return true;
        }

        VkResult endCommandBufferRes = vkEndCommandBuffer(*cmBuffer->commandBufferHandler);

        if (endCommandBufferRes != VK_SUCCESS)
        {
            Picasso::Engine::Logger::Logger::Error("Unable to end recording for a command buffer");
            return false;
        }

        cmBuffer->state = COMMAND_BUFFER_STATE_END_RECORDING;

        return true;
    }

    bool VulkanCommandBuffer::ExecuteCommand(DriverContext *context, std::shared_ptr<VulkanCommandBufferDto> cmBuffer)
    {
        VkSubmitInfo submitInfo = {VK_STRUCTURE_TYPE_SUBMIT_INFO};
        VkPipelineStageFlags sFlags[1] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = cmBuffer->commandBufferHandler.get();
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = context->queueCompleteSemaphores[context->currentFrame].get();
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = context->imageAvailableSemaphores[context->currentFrame].get();
        submitInfo.pWaitDstStageMask = sFlags;

        VkResult executeCommandRes = vkQueueSubmit(context->devices.graphicsQueue, 1, &submitInfo, context->fences[context->currentFrame]->handler);

        if (executeCommandRes != VK_SUCCESS)
        {
            Picasso::Engine::Logger::Logger::Error("Unable to execute the command buffer");
            return false;
        }

        // set in state submitted
        this->Submitted(cmBuffer);

        return true;
    }

    void VulkanCommandBuffer::Submitted(std::shared_ptr<VulkanCommandBufferDto> cmBuffer)
    {
        cmBuffer->state = COMMAND_BUFFER_STATE_SUBMITTED;
    }

    void VulkanCommandBuffer::Reset(std::shared_ptr<VulkanCommandBufferDto> cmBuffer)
    {
        cmBuffer->state = COMMAND_BUFFER_STATE_READY;
    }

    std::shared_ptr<VulkanCommandBufferDto> VulkanCommandBuffer::BuildSingleUse(DriverContext *context, VkCommandPool pool)
    {
        std::shared_ptr<VulkanCommandBufferDto> cmBuffer = this->Allocate(context, pool, true);

        if (cmBuffer == nullptr)
        {
            return nullptr;
        }

        if (!this->BeginRecording(cmBuffer, true, false, false))
        {
            return nullptr;
        }

        return cmBuffer;
    }

    bool VulkanCommandBuffer::EndSingleUse(DriverContext *context, VkCommandPool pool, std::shared_ptr<VulkanCommandBufferDto> cmBuffer, VkQueue queue)
    {
        if (!this->EndRecording(cmBuffer))
        {
            return false;
        }

        VkSubmitInfo submitInfo = {VK_STRUCTURE_TYPE_SUBMIT_INFO};

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = cmBuffer->commandBufferHandler.get();

        VkResult queueSubmit = vkQueueSubmit(queue, 1, &submitInfo, 0);

        if (queueSubmit != VK_SUCCESS)
        {
            Picasso::Engine::Logger::Logger::Error("Unable to submit command buffer to the queue");
            return false;
        }

        VkResult queueExecuted = vkQueueWaitIdle(queue);

        if (queueExecuted != VK_SUCCESS)
        {
            Picasso::Engine::Logger::Logger::Error("Queue has not been executed");
            return false;
        }

        this->Free(context, pool, cmBuffer);

        return true;
    }

    bool VulkanCommandBuffer::_createCommandPool(DriverContext *context)
    {
        VkCommandPoolCreateInfo cmPoolCreateInfo = {VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO};

        cmPoolCreateInfo.queueFamilyIndex = context->devices.graphicsQueueIndex;
        cmPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

        VkResult createPoolRes = vkCreateCommandPool(context->devices.logicalDevice, &cmPoolCreateInfo, 0, &context->pool);

        if (createPoolRes != VK_SUCCESS)
        {
            Picasso::Engine::Logger::Logger::Error("Cannot create the command pool");
            return false;
        }

        return true;
    }
}