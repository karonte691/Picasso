#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanFenceManager.h>

namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
    std::shared_ptr<VulkanFence> VulkanFenceManager::Create(DriverContext *context, bool isSignaled)
    {
        std::shared_ptr<VulkanFence> vFence = std::make_shared<VulkanFence>();

        vFence->isSignaled = isSignaled;

        VkFenceCreateInfo fCreateInfo = {VK_STRUCTURE_TYPE_FENCE_CREATE_INFO};

        if (isSignaled)
        {
            fCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
        }

        VkResult createFenceRes = vkCreateFence(context->devices.logicalDevice,
                                                &fCreateInfo,
                                                0,
                                                &vFence->handler);

        if (createFenceRes != VK_SUCCESS)
        {
            Picasso::Engine::Logger::Logger::Error("Unable to create the Vulkan fence");
            return nullptr;
        }

        return vFence;
    }

    bool VulkanFenceManager::Reset(DriverContext *context, std::shared_ptr<VulkanFence> vFence)
    {
        if (!vFence->isSignaled)
        {
            return true;
        }

        VkResult resetFenceRes = vkResetFences(context->devices.logicalDevice, 1, &vFence->handler);

        if (resetFenceRes != VK_SUCCESS)
        {
            return false;
        }

        vFence->isSignaled = false;

        return true;
    }

    void VulkanFenceManager::Destroy(DriverContext *context, std::shared_ptr<VulkanFence> vFence)
    {
        if (vFence->handler)
        {
            vkDestroyFence(context->devices.logicalDevice, vFence->handler, 0);
            vFence->handler = 0;
        }

        vFence->isSignaled = false;
    }

    bool VulkanFenceManager::Wait(DriverContext *context, std::shared_ptr<VulkanFence> vFence, u_int timeout)
    {
        if (vFence->isSignaled)
        {
            return true;
        }

        VkResult waitForFencesRes = vkWaitForFences(context->devices.logicalDevice, 1, &vFence->handler, true, timeout);

        if (waitForFencesRes != VK_SUCCESS)
        {
            this->_printFenceResultError(waitForFencesRes);
            return false;
        }

        vFence->isSignaled = true;

        return true;
    }

    void VulkanFenceManager::_printFenceResultError(VkResult error)
    {
        switch (error)
        {
        case VK_TIMEOUT:
            Picasso::Engine::Logger::Logger::Warn("vkWaitForFences() - Timed out");
            break;
        case VK_ERROR_DEVICE_LOST:
            Picasso::Engine::Logger::Logger::Warn("vkWaitForFences() - VK_ERROR_DEVICE_LOST.");
            break;
        case VK_ERROR_OUT_OF_HOST_MEMORY:
            Picasso::Engine::Logger::Logger::Warn("vkWaitForFences() - VK_ERROR_OUT_OF_HOST_MEMORY.");
            break;
        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            Picasso::Engine::Logger::Logger::Warn("vkWaitForFences() - VK_ERROR_OUT_OF_DEVICE_MEMORY.");
            break;
        default:
            Picasso::Engine::Logger::Logger::Warn("vkWaitForFences() - An unknown error has occurred.");
            break;
        }
    }
}