#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanImageCreator.h>

namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
    VulkanImageCreator::VulkanImageCreator()
    {
        m_driverMemory = new VulkanMemory();
    }

    VulkanImageCreator::~VulkanImageCreator()
    {
        delete m_driverMemory;
        m_driverMemory = nullptr;
    }

    std::shared_ptr<VulkanImage> VulkanImageCreator::Create(DriverContext *context, VulkanImageCreateInfo imageCreateInfo)
    {
        std::shared_ptr<VulkanImage> vImage = std::make_shared<VulkanImage>();

        vImage->width = imageCreateInfo.width;
        vImage->height = imageCreateInfo.height;

        VkImageCreateInfo vImageInfo = this->_createImageInfo(imageCreateInfo);

        VkResult createImageResult = vkCreateImage(context->devices.logicalDevice, &vImageInfo, 0, &vImage->imageHandler);

        if (createImageResult != VK_SUCCESS)
        {
            Picasso::Engine::Logger::Logger::Error("VulkanImageCreator: unable to create the image");
            return nullptr;
        }

        VkMemoryRequirements memoryRequirements;
        context->memoryIndex = m_driverMemory->FindMemoryIndex(context, memoryRequirements.memoryTypeBits, imageCreateInfo.memoryFlags);

        if (context->memoryIndex == -1)
        {
            Picasso::Engine::Logger::Logger::Error("VulkanImageCreator: required memory requirement not found. Image not valid");
            return nullptr;
        }

        vkGetImageMemoryRequirements(context->devices.logicalDevice, vImage->imageHandler, &memoryRequirements);

        VkMemoryAllocateInfo vMemoryAllocateInfo = this->_getMemoryAllocateInfo(memoryRequirements, context->memoryIndex);

        VkResult allocateMemoryRes = vkAllocateMemory(context->devices.logicalDevice, &vMemoryAllocateInfo, 0, &vImage->deviceMemory);

        if (allocateMemoryRes != VK_SUCCESS)
        {
            Picasso::Engine::Logger::Logger::Error("VulkanImageCreator: could not allocate memory");
            return nullptr;
        }

        VkResult bindMemoryResult = vkBindImageMemory(context->devices.logicalDevice, vImage->imageHandler, vImage->deviceMemory, 0);

        if (bindMemoryResult != VK_SUCCESS)
        {
            Picasso::Engine::Logger::Logger::Error("VulkanImageCreator: could not bind memory");
            return nullptr;
        }

        if (imageCreateInfo.createView)
        {
            vImage->imageView = 0;
            if (this->_createImageView(context, imageCreateInfo.imageFormat, vImage, imageCreateInfo.imageAspectFlags))
            {
                return nullptr;
            }
        }

        return vImage;
    }

    void VulkanImageCreator::Destroy(DriverContext *context, std::shared_ptr<VulkanImage> vImage)
    {
        if (vImage->imageView)
        {
            vkDestroyImageView(context->devices.logicalDevice, vImage->imageView, 0);
        }

        if (vImage->deviceMemory)
        {
            vkFreeMemory(context->devices.logicalDevice, vImage->deviceMemory, 0);
        }

        if (vImage->imageHandler)
        {
            vkDestroyImage(context->devices.logicalDevice, vImage->imageHandler, 0);
        }

        vImage = nullptr;
    }

    bool VulkanImageCreator::_createImageView(DriverContext *context, VkFormat format, std::shared_ptr<VulkanImage> vImage, VkImageAspectFlags imageFlag)
    {
        VkImageViewCreateInfo vImageViewCreateInfo = this->_createImageViewInfo(format, vImage, imageFlag);

        VkResult createImageView = vkCreateImageView(context->devices.logicalDevice, &vImageViewCreateInfo, 0, &vImage->imageView);

        if (createImageView != VK_SUCCESS)
        {
            Picasso::Engine::Logger::Logger::Error("VulkanImageCreator: could not bind memory");
            return false;
        }

        return true;
    }

    VkImageCreateInfo VulkanImageCreator::_createImageInfo(VulkanImageCreateInfo imageCreateInfo)
    {
        VkImageCreateInfo vImageInfo = {VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO};

        vImageInfo.imageType = VK_IMAGE_TYPE_2D;
        vImageInfo.extent.width = imageCreateInfo.width;
        vImageInfo.extent.height = imageCreateInfo.height;
        vImageInfo.extent.depth = 1;
        vImageInfo.mipLevels = 4;
        vImageInfo.arrayLayers = 1;
        vImageInfo.format = imageCreateInfo.imageFormat;
        vImageInfo.tiling = imageCreateInfo.imageTiling;
        vImageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        vImageInfo.usage = imageCreateInfo.imageUsageflags;
        vImageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        vImageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        return vImageInfo;
    }

    VkMemoryAllocateInfo VulkanImageCreator::_getMemoryAllocateInfo(VkMemoryRequirements memoryRequirements, u_int32_t memoryType)
    {
        VkMemoryAllocateInfo memoryAllocateInfo = {VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO};

        memoryAllocateInfo.allocationSize = memoryRequirements.size;
        memoryAllocateInfo.memoryTypeIndex = memoryType;

        return memoryAllocateInfo;
    }

    VkImageViewCreateInfo VulkanImageCreator::_createImageViewInfo(VkFormat format, std::shared_ptr<VulkanImage> vImage, VkImageAspectFlags imageFlag)
    {
        VkImageViewCreateInfo imageViewCreateInfo = {VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO};

        imageViewCreateInfo.image = vImage->imageHandler;
        imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        imageViewCreateInfo.format = format;
        imageViewCreateInfo.subresourceRange.aspectMask = imageFlag;

        imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
        imageViewCreateInfo.subresourceRange.levelCount = 1;
        imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
        imageViewCreateInfo.subresourceRange.layerCount = 1;

        return imageViewCreateInfo;
    }
}
