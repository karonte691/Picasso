#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanSwapChainManager.h>
#include <bits/stdc++.h>
namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
    bool VulkanSwapChainManager::Create(DriverContext *context, u_int32_t width, u_int32_t height, std::shared_ptr<VulkanDevice> m_device)
    {
        if (m_imageManager == nullptr)
        {
            m_imageManager = std::make_unique<VulkanImageManager>(m_device);
        }

        if (m_imageCreateOptions == nullptr)
        {
            m_imageCreateOptions = new VulkanImageCreateOptions();
        }

        return this->_createSwapChain(context, width, height);
    }

    void VulkanSwapChainManager::Destroy(DriverContext *context)
    {
        if (context->swapChain->vImage != nullptr)
        {
            m_imageManager->Destroy(context, context->swapChain->vImage);

            // destroying image views
            for (u_int32_t i = 0; i < m_swapChain->imageCount; ++i)
            {
                vkDestroyImageView(context->devices.logicalDevice, m_swapChain->imageViews[i], 0);
            }

            context->swapChain->vImage = nullptr;
        }

        vkDestroySwapchainKHR(context->devices.logicalDevice, m_swapChain->scHandler, 0);

        delete m_imageCreateOptions;
        m_imageCreateOptions = nullptr;

        m_swapChain = nullptr;
        context->swapChain = nullptr;
    }

    bool VulkanSwapChainManager::_createSwapChain(DriverContext *context, u_int32_t width, u_int32_t height)
    {
        VkExtent2D scExtent = {width, height};
        m_swapChain = std::make_shared<VulkanSwapChain>();

        m_swapChain->maxRenderFrames = 2;

        m_device->QuerySwapChainSupport(context->devices.physicalDevice, context->surface, &context->devices.swapChainSupport);

        // get image format
        bool gotImageFormat = false;

        Picasso::Engine::Logger::Logger::Info("Formats found: %d", context->devices.swapChainSupport.formatCount);

        for (u_int32_t i = 0; i < context->devices.swapChainSupport.formatCount; ++i)
        {
            VkSurfaceFormatKHR format = context->devices.swapChainSupport.formats[i];

            if (format.format == VK_FORMAT_B8G8R8_UNORM && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
            {
                m_swapChain->imageFormat = format;
                gotImageFormat = true;
                break;
            }
        }

        if (!gotImageFormat)
        {
            // get the first one available
            m_swapChain->imageFormat = context->devices.swapChainSupport.formats[0];
        }

        VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;

        Picasso::Engine::Logger::Logger::Info("Present modes found: %d", context->devices.swapChainSupport.presentModeCount);

        for (u_int32_t i = 0; i < context->devices.swapChainSupport.presentModeCount; ++i)
        {
            VkPresentModeKHR mode = context->devices.swapChainSupport.presentMode[i];

            if (mode == VK_PRESENT_MODE_MAILBOX_KHR)
            {
                presentMode = mode;
                break;
            }
        }

        m_device->QuerySwapChainSupport(context->devices.physicalDevice, context->surface, &context->devices.swapChainSupport);

        this->_calculateExtentDimension(context, scExtent);
        u_int32_t imageCount = this->_getImageCount(context);

        VkSwapchainCreateInfoKHR *swcCreateInfo = this->_getSwapChainCreateInfo(context,
                                                                                imageCount,
                                                                                scExtent,
                                                                                presentMode);

        VkResult swcCreateOpResult = vkCreateSwapchainKHR(context->devices.logicalDevice, swcCreateInfo, 0, &m_swapChain->scHandler);

        if (swcCreateOpResult != VK_SUCCESS)
        {
            Picasso::Engine::Logger::Logger::Error("Unable to create the swap chain");
            return false;
        }

        // get the image count and create it
        if (!this->_createSwapChainImages(context))
        {
            return false;
        }

        // detect depth format
        if (!m_device->DetectDepthFormat(context))
        {
            Picasso::Engine::Logger::Logger::Fatal("Unable to find a supported format");
            return false;
        }

        m_imageCreateOptions->imageType = VK_IMAGE_TYPE_2D;
        m_imageCreateOptions->width = scExtent.width;
        m_imageCreateOptions->height = scExtent.height;
        m_imageCreateOptions->imageFormat = context->devices.depthFormat;
        m_imageCreateOptions->imageTiling = VK_IMAGE_TILING_OPTIMAL;
        m_imageCreateOptions->imageUsageflags = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
        m_imageCreateOptions->memoryFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
        m_imageCreateOptions->createView = true;
        m_imageCreateOptions->imageAspectFlags = VK_IMAGE_ASPECT_DEPTH_BIT;

        m_swapChain->vImage = m_imageManager->Create(context, m_imageCreateOptions);

        context->swapChain = m_swapChain;

        Picasso::Engine::Logger::Logger::Info("Swap chain created succesfully");

        return true;
    }

    bool VulkanSwapChainManager::_createSwapChainImages(DriverContext *context)
    {
        // reset just to be sure
        context->imageIndex = 0;
        context->currentFrame = 0;

        VkResult swGetImagesCount = vkGetSwapchainImagesKHR(context->devices.logicalDevice, m_swapChain->scHandler, &m_swapChain->imageCount, 0);

        if (swGetImagesCount != VK_SUCCESS)
        {
            Picasso::Engine::Logger::Logger::Error("Unable to get the swap chain images..");
            return false;
        }

        if (m_swapChain->images == nullptr)
        {
            m_swapChain->images = std::make_unique<VkImage[]>(m_swapChain->imageCount);
        }

        if (m_swapChain->imageViews == nullptr)
        {
            m_swapChain->imageViews = std::make_unique<VkImageView[]>(m_swapChain->imageCount);
        }

        VkResult swGetImages = vkGetSwapchainImagesKHR(context->devices.logicalDevice, m_swapChain->scHandler, &m_swapChain->imageCount, m_swapChain->images.get());

        if (swGetImages != VK_SUCCESS)
        {
            Picasso::Engine::Logger::Logger::Error("Unable to get the swap chain images..");
            return false;
        }

        VkImageViewCreateInfo vInfo = {VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO};
        VkResult createImageViewRes = {VK_NOT_READY};

        for (u_int32_t i = 0; i < m_swapChain->imageCount; ++i)
        {
            vInfo.image = m_swapChain->images[i];
            vInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            vInfo.format = m_swapChain->imageFormat.format;
            vInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            vInfo.subresourceRange.baseMipLevel = 0;
            vInfo.subresourceRange.levelCount = 1;
            vInfo.subresourceRange.baseArrayLayer = 0;
            vInfo.subresourceRange.layerCount = 1;

            createImageViewRes = vkCreateImageView(context->devices.logicalDevice, &vInfo, 0, &m_swapChain->imageViews[i]);

            if (createImageViewRes != VK_SUCCESS)
            {
                Picasso::Engine::Logger::Logger::Error("Unable to create swapchain image..");
                return false;
            }

            // reset
            vInfo = {VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO};
            createImageViewRes = {VK_NOT_READY};
        }

        return true;
    }

    void VulkanSwapChainManager::_reCreateSwapChain(DriverContext *context, u_int32_t width, u_int32_t height)
    {
        this->Destroy(context);
        this->_createSwapChain(context, width, height);
    }

    bool VulkanSwapChainManager::_fetchNextImageIndex(DriverContext *context, u_int64_t timeout, VkSemaphore imageSemaphore, VkFence fences)
    {
        VkResult acqImageResult = vkAcquireNextImageKHR(context->devices.logicalDevice,
                                                        m_swapChain->scHandler,
                                                        timeout,
                                                        imageSemaphore,
                                                        fences,
                                                        m_imageIndex.get());

        if (acqImageResult == VK_ERROR_OUT_OF_DATE_KHR)
        {
            Picasso::Engine::Logger::Logger::Debug("Fetching next image returned VK_ERROR_OUT_OF_DATE_KHR. Recreating the swapchain..");
            this->_reCreateSwapChain(context, context->frameBufferWidth, context->frameBufferHeight);

            return false;
        }

        if (acqImageResult != VK_SUCCESS && acqImageResult != VK_SUBOPTIMAL_KHR)
        {
            Picasso::Engine::Logger::Logger::Error("Failed to fetch the next image in the swap chain");
            return false;
        }

        return true;
    }

    void VulkanSwapChainManager::_swapChainPresent(DriverContext *context, VkQueue graphicsQueue, VkQueue presentQueue, VkSemaphore renderComplete)
    {
        VkPresentInfoKHR presentInfo = {VK_STRUCTURE_TYPE_PRESENT_INFO_KHR};

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = &renderComplete;
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = &m_swapChain->scHandler;
        presentInfo.pImageIndices = m_imageIndex.get();
        presentInfo.pResults = 0;

        VkResult queuePresentResult = vkQueuePresentKHR(presentQueue, &presentInfo);

        if (queuePresentResult == VK_ERROR_OUT_OF_DATE_KHR || queuePresentResult == VK_SUBOPTIMAL_KHR)
        {
            Picasso::Engine::Logger::Logger::Debug("Presenting next image returned VK_ERROR_OUT_OF_DATE_KHR or VK_SUBOPTIMAL_KHR. Recreating the swapchain..");
            this->_reCreateSwapChain(context, context->frameBufferWidth, context->frameBufferHeight);

            return;
        }

        if (queuePresentResult == VK_SUCCESS)
        {
            return;
        }

        Picasso::Engine::Logger::Logger::Fatal("Failed to present the next image in the swap chain");
    }

    void VulkanSwapChainManager::_calculateExtentDimension(DriverContext *context, VkExtent2D &extent)
    {
        // if the width given in input is invalid, we set the extent to the current capabilities
        if (context->devices.swapChainSupport.capabilities.currentExtent.width != UINT32_MAX)
        {
            extent = context->devices.swapChainSupport.capabilities.currentExtent;
        }

        VkExtent2D minExt = context->devices.swapChainSupport.capabilities.minImageExtent;
        VkExtent2D maxExt = context->devices.swapChainSupport.capabilities.maxImageExtent;

        extent.width = std::clamp(extent.width, minExt.width, maxExt.width);
        extent.height = std::clamp(extent.height, minExt.height, maxExt.height);
    }

    u_int32_t VulkanSwapChainManager::_getImageCount(DriverContext *context)
    {
        u_int32_t imgCount = context->devices.swapChainSupport.capabilities.minImageCount + 1;

        // safeguad
        if (context->devices.swapChainSupport.capabilities.maxImageCount > 0 &&
            imgCount > context->devices.swapChainSupport.capabilities.maxImageCount)
        {
            imgCount = context->devices.swapChainSupport.capabilities.maxImageCount;
        }

        return imgCount;
    }

    VkSwapchainCreateInfoKHR *VulkanSwapChainManager::_getSwapChainCreateInfo(DriverContext *context,
                                                                              u_int32_t imageCount,
                                                                              VkExtent2D extent,
                                                                              VkPresentModeKHR presentMode)
    {
        VkSwapchainCreateInfoKHR *scCreateInfo = new VkSwapchainCreateInfoKHR{VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR};

        scCreateInfo->surface = context->surface;
        scCreateInfo->minImageCount = imageCount;
        scCreateInfo->imageFormat = m_swapChain->imageFormat.format;
        scCreateInfo->imageColorSpace = m_swapChain->imageFormat.colorSpace;
        scCreateInfo->imageExtent = extent;
        scCreateInfo->imageArrayLayers = 1;
        scCreateInfo->imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        if (context->devices.graphicsQueueIndex != context->devices.presentQueueIndex)
        {
            u_int32_t queueFamilyIndex[] = {(u_int32_t)context->devices.graphicsQueueIndex, (u_int32_t)context->devices.presentQueueIndex};

            scCreateInfo->imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            scCreateInfo->queueFamilyIndexCount = 2;
            scCreateInfo->pQueueFamilyIndices = queueFamilyIndex;
        }
        else
        {
            scCreateInfo->imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            scCreateInfo->queueFamilyIndexCount = 0;
            scCreateInfo->pQueueFamilyIndices = 0;
        }

        scCreateInfo->preTransform = context->devices.swapChainSupport.capabilities.currentTransform;
        scCreateInfo->compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        scCreateInfo->presentMode = presentMode;
        scCreateInfo->clipped = VK_TRUE;
        scCreateInfo->oldSwapchain = 0;

        return scCreateInfo;
    }
}