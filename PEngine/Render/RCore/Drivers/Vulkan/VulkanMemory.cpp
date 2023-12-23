#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanMemory.h>

namespace Picasso::Engine::Render::Core::Drivers
{
    int32_t VulkanMemory::FindMemoryIndex(DriverContext *context, u_int32_t typeFilter, u_int32_t propertyFlags)
    {
        VkPhysicalDeviceMemoryProperties memoryProps;
        vkGetPhysicalDeviceMemoryProperties(context->devices.physicalDevice, &memoryProps);

        for (u_int32_t i = 0; i < memoryProps.memoryTypeCount; i++)
        {
            if (typeFilter & (1 << i) &&
                (memoryProps.memoryTypes[i].propertyFlags & propertyFlags) == propertyFlags)
            {
                return i;
            }
        }

        Picasso::Engine::Logger::Logger::Error("Could not find memory index");
        return -1;
    }
}