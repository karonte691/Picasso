#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanCommandBuffer.h>

namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
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
}