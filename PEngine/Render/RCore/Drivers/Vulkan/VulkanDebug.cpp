#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDebug.h>

#include <algorithm>

std::vector<const char *> Picasso::Engine::Render::Core::Drivers::Vulkan::VulkanDebug::GetValidationLayerList()
{
    std::vector<const char *> reqValidationLayes(1);

    reqValidationLayes.push_back("VK_LAYER_KHRONOS_validation");

        return reqValidationLayes;
}

void Picasso::Engine::Render::Core::Drivers::Vulkan::VulkanDebug::PrintDeviceWaitError(VkResult error)
{
    switch (error)
    {
    case VK_TIMEOUT:
        Picasso::Engine::Logger::Logger::Warn("Timed out");
        break;
    case VK_ERROR_DEVICE_LOST:
        Picasso::Engine::Logger::Logger::Warn("VK_ERROR_DEVICE_LOST.");
        break;
    case VK_ERROR_OUT_OF_HOST_MEMORY:
        Picasso::Engine::Logger::Logger::Warn("VK_ERROR_OUT_OF_HOST_MEMORY.");
        break;
    case VK_ERROR_OUT_OF_DEVICE_MEMORY:
        Picasso::Engine::Logger::Logger::Warn("VK_ERROR_OUT_OF_DEVICE_MEMORY.");
        break;
    default:
        Picasso::Engine::Logger::Logger::Warn("An unknown error has occurred.");
        break;
    }
}