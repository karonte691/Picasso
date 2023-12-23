#pragma once

#ifndef VULKAN_IMAGE_CREATOR_H
#define VULKAN_IMAGE_CREATOR_H

#include <PEngine/Logger/Logger.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDriverData.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanMemory.h>
#include <memory>

namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
    class VulkanImageCreator
    {
    public:
        VulkanImageCreator();
        ~VulkanImageCreator();

        std::shared_ptr<VulkanImage> Create(DriverContext *context, VulkanImageCreateInfo imageCreateInfo);
        void Destroy(DriverContext *context, std::shared_ptr<VulkanImage> vImage);

    private:
        VulkanMemory *m_driverMemory;
        VkImageCreateInfo _createImageInfo(VulkanImageCreateInfo imageCreateInfo);
        VkMemoryAllocateInfo _getMemoryAllocateInfo(VkMemoryRequirements memoryRequirements, u_int32_t memoryType);
        VkImageViewCreateInfo _createImageViewInfo(VkFormat format, std::shared_ptr<VulkanImage> vImage, VkImageAspectFlags imageFlag);

        bool _createImageView(DriverContext *context, VkFormat format, std::shared_ptr<VulkanImage> vImage, VkImageAspectFlags imageFlag);
    };
}
#endif