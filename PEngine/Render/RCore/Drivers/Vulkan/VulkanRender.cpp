#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanRender.h>

namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
    VulkanRender::VulkanRender()
    {
        p_GraphicsPipeline = new VulkanGraphicsPipeline();
        p_commandBufferManager = new VulkanCommandBuffer();
        p_FrameBufferManager = new VulkanFrameBuffer();
        p_FenceManager = new VulkanFenceManager();
    }

    bool VulkanRender::SetUp(DriverContext *context, u_int32_t swapChainImageCount, std::shared_ptr<PPlatformState> pState)
    {
        if (!p_commandBufferManager->DecorateContext(context, swapChainImageCount))
        {
            return false;
        }

        Picasso::Engine::Logger::Logger::Debug("Command pool created succesfully");

        if (!this->_initFences(context))
        {
            return false;
        }

        Picasso::Engine::Logger::Logger::Debug("Fences created succesfully");

        if (!this->_decorateContext(context))
        {
            return false;
        }

        Picasso::Engine::Logger::Logger::Debug("Render pass created succesfully");

        if (!this->RegenerateFrameBuffer(context, pState))
        {
            return false;
        }

        Picasso::Engine::Logger::Logger::Debug("Frame buffer created succesfully");

        return true;
    }

    void VulkanRender::Clear(DriverContext *context)
    {
        // wait until no ops running
        vkDeviceWaitIdle(context->devices.logicalDevice);

        for (u_int32_t i = 0; i < context->swapChain->maxRenderFrames; ++i)
        {
            if (context->imageAvailableSemaphores[i])
            {
                vkDestroySemaphore(context->devices.logicalDevice, *context->imageAvailableSemaphores[i], 0);
                context->imageAvailableSemaphores[i] = nullptr;
            }

            if (context->queueCompleteSemaphores[i])
            {
                vkDestroySemaphore(context->devices.logicalDevice, *context->queueCompleteSemaphores[i], 0);
                context->queueCompleteSemaphores[i] = nullptr;
            }

            p_FenceManager->Destroy(context, context->fences[i]);
        }

        context->imageAvailableSemaphores.clear();
        context->queueCompleteSemaphores.clear();
        context->fences.clear();
        context->imgInFlight.clear();

        p_commandBufferManager->Clear(context);
        p_FrameBufferManager->Clear(context, context->swapChain->frameBuffers);
        context->cmBuffers.clear();
        p_GraphicsPipeline->RenderPassDestroy(context, context->renderPass.get());

        delete p_commandBufferManager;
        p_commandBufferManager = nullptr;

        delete p_GraphicsPipeline;
        p_GraphicsPipeline = nullptr;

        delete p_FrameBufferManager;
        p_FrameBufferManager = nullptr;

        delete p_FenceManager;
        p_FenceManager = nullptr;
    }

    bool VulkanRender::BeginRenderFrame(DriverContext *context)
    {
        std::shared_ptr<VulkanCommandBufferDto> cmBuffer = context->cmBuffers[context->imageIndex];

        this->p_commandBufferManager->Reset(cmBuffer);

        if (!this->p_commandBufferManager->BeginRecording(cmBuffer, false, false, false))
        {
            return false;
        }

        VkViewport vPort = this->_getViewPort(context);
        VkRect2D scissor = this->_getScissor(context);

        p_commandBufferManager->ConfigureViewPort(cmBuffer, &vPort);
        p_commandBufferManager->ConfigureScissor(cmBuffer, &scissor);

        context->renderPass->area.w = context->frameBufferWidth;
        context->renderPass->area.h = context->frameBufferHeight;

        p_GraphicsPipeline->RenderPassBegin(cmBuffer.get(), context->renderPass.get(), context->swapChain->frameBuffers[context->imageIndex]->handler);

        return true;
    }

    bool VulkanRender::EndRenderFrame(DriverContext *context)
    {
        std::shared_ptr<VulkanCommandBufferDto> cmBuffer = context->cmBuffers[context->imageIndex];

        p_GraphicsPipeline->RenderPassEnd(cmBuffer.get(), context->renderPass.get());

        if (!this->p_commandBufferManager->EndRecording(cmBuffer))
        {
            return false;
        }

        if (context->imgInFlight[context->imageIndex] != nullptr)
        {
            if (!this->Wait(context))
            {
                return false;
            }
        }

        // mark as used by the frame
        context->imgInFlight[context->currentFrame] = context->fences[context->currentFrame];

        if (!p_FenceManager->Reset(context, context->fences[context->currentFrame]))
        {
            return false;
        }

        return p_commandBufferManager->ExecuteCommand(context, cmBuffer);
    }

    bool VulkanRender::Wait(DriverContext *context)
    {
        if (context->currentFrame >= context->fences.size())
        {
            Picasso::Engine::Logger::Logger::Warn("currentFrame index greater than fences array: %d -> %d", context->cmBuffers, context->fences.size());
            return true;
        }

        if (context->fences[context->currentFrame] == nullptr)
        {
            return true;
        }

        return p_FenceManager->Wait(context, context->fences[context->currentFrame], UINT64_MAX);
    }

    void VulkanRender::CleanUpBuffers(DriverContext *context)
    {
        for (u_int32_t i = 0; i < context->swapChain->imageCount; ++i)
        {
            p_commandBufferManager->Free(context, context->pool, context->cmBuffers[i]);
        }

        p_FrameBufferManager->Clear(context, context->swapChain->frameBuffers);
    }

    bool VulkanRender::RegenerateFrameBuffer(DriverContext *context, std::shared_ptr<PPlatformState> pState)
    {
        context->swapChain->frameBuffers.resize(context->swapChain->imageCount);

        u_int32_t attachmentCount = 2;

        for (u_int32_t i = 0; i < context->swapChain->imageCount; ++i)
        {
            VkImageView attachments[attachmentCount] = {
                context->swapChain->imageViews[i],
                context->swapChain->vImage->imageView};

            std::shared_ptr<VulkanFrameBufferDto> frameBufferDto = p_FrameBufferManager->DecorateContext(context,
                                                                                                         context->renderPass,
                                                                                                         context->frameBufferWidth,
                                                                                                         context->frameBufferHeight,
                                                                                                         attachmentCount,
                                                                                                         attachments);

            if (frameBufferDto == nullptr)
            {
                Picasso::Engine::Logger::Logger::Fatal("Unable to create the frame buffer for image index %d", i);
                return false;
            }

            context->swapChain->frameBuffers[i] = frameBufferDto;
        }

        return true;
    }

    bool VulkanRender::RegenerateCommandBuffer(DriverContext *context)
    {
        return p_commandBufferManager->DecorateContext(context, context->swapChain->imageCount);
    }

    bool VulkanRender::_initFences(DriverContext *context)
    {
        context->imageAvailableSemaphores.resize(context->swapChain->maxRenderFrames);
        context->queueCompleteSemaphores.resize(context->swapChain->maxRenderFrames);
        context->fences.resize(context->swapChain->maxRenderFrames);
        context->imgInFlight.resize(context->swapChain->maxRenderFrames);

        VkSemaphoreCreateInfo sCreateInfo = {VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO};

        for (u_int32_t i = 0; i < context->swapChain->maxRenderFrames; ++i)
        {
            context->imageAvailableSemaphores[i] = std::make_shared<VkSemaphore>();

            VkResult createSemaphoreRes = vkCreateSemaphore(context->devices.logicalDevice,
                                                            &sCreateInfo,
                                                            0,
                                                            context->imageAvailableSemaphores[i].get());

            if (createSemaphoreRes != VK_SUCCESS)
            {
                Picasso::Engine::Logger::Logger::Error("Unable to create the Vulkan Semaphore for frame %d", i);
                return false;
            }

            context->queueCompleteSemaphores[i] = std::make_shared<VkSemaphore>();

            VkResult createCompSemaphoreRes = vkCreateSemaphore(context->devices.logicalDevice,
                                                                &sCreateInfo,
                                                                0,
                                                                context->queueCompleteSemaphores[i].get());

            if (createCompSemaphoreRes != VK_SUCCESS)
            {
                Picasso::Engine::Logger::Logger::Error("Unable to create the Vulkan Semaphore for frame %d", i);
                return false;
            }

            std::shared_ptr<VulkanFence> vFence = p_FenceManager->Create(context, true);

            if (vFence == nullptr)
            {
                return false;
            }

            context->imgInFlight[i] = 0;
            context->fences[i] = vFence;
        }

        return true;
    }

    bool VulkanRender::_decorateContext(DriverContext *context)
    {
        float fbWidth = static_cast<float>(context->frameBufferWidth);
        float fbHeight = static_cast<float>(context->frameBufferHeight);

        VulkanRenderPassArea area = {0, 0, fbWidth, fbHeight};
        VulkanRenderPassColor color = {0.0f, 0.0f, 0.2f, 1.0f};

        VulkanRenderPass rpData = p_GraphicsPipeline->RenderPassCreate(context, area, color, 1.0f, 0);

        if (!rpData.isValid())
        {
            // render pass data is corrupted, exiting..
            Picasso::Engine::Logger::Logger::Fatal("render pass data is corrupted,");
            return false;
        }

        context->renderPass = std::make_shared<VulkanRenderPass>(rpData);

        return true;
    }

    VkViewport VulkanRender::_getViewPort(const DriverContext *context)
    {
        VkViewport vPort;
        float fbWidth = static_cast<float>(context->frameBufferWidth);
        float fbHeight = static_cast<float>(context->frameBufferHeight);

        vPort.x = 0.0f;
        vPort.y = fbHeight;
        vPort.width = fbWidth;
        vPort.height = -fbHeight;
        vPort.minDepth = 0.0f;
        vPort.maxDepth = 1.0f;

        return vPort;
    }

    VkRect2D VulkanRender::_getScissor(const DriverContext *context)
    {
        VkRect2D scissor;

        scissor.offset.x = 0;
        scissor.offset.y = 0;
        scissor.extent.width = context->frameBufferWidth;
        scissor.extent.height = context->frameBufferHeight;

        return scissor;
    }
}