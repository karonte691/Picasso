#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanRender.h>

namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
    VulkanRender::VulkanRender()
    {
        p_GraphicsPipeline = new VulkanGraphicsPipeline();
        p_commandBufferManager = new VulkanCommandBuffer();
        p_FrameBufferManager = new VulkanFrameBuffer();
    }

    bool VulkanRender::SetUp(DriverContext *context, u_int32_t swapChainImageCount, std::shared_ptr<PPlatformState> pState)
    {

        if (!p_commandBufferManager->DecorateContext(context, swapChainImageCount))
        {
            return false;
        }

        Picasso::Engine::Logger::Logger::Debug("Command pool created succesfully");

        if (!this->_decorateContext(context))
        {
            return false;
        }

        Picasso::Engine::Logger::Logger::Debug("Render pass created succesfully");

        if (!this->_regenerateFrameBuffer(context, pState))
        {
            return false;
        }

        Picasso::Engine::Logger::Logger::Debug("Frame buffer created succesfully");

        return true;
    }

    void VulkanRender::Clear(DriverContext *context)
    {
        p_commandBufferManager->Clear(context);

        this->_clearContext(context);

        delete p_commandBufferManager;
        p_commandBufferManager = nullptr;

        delete p_GraphicsPipeline;
        p_GraphicsPipeline = nullptr;

        delete p_FrameBufferManager;
        p_FrameBufferManager = nullptr;
    }

    bool VulkanRender::_decorateContext(DriverContext *context)
    {
        _Float32 fbWidth = static_cast<_Float32>(context->frameBufferWidth);
        _Float32 fbHeight = static_cast<_Float32>(context->frameBufferHeight);

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

    bool VulkanRender::_regenerateFrameBuffer(DriverContext *context, std::shared_ptr<PPlatformState> pState)
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

    void VulkanRender::_clearContext(DriverContext *context)
    {
        context->cmBuffers->clear();
        delete context->cmBuffers;
        context->cmBuffers = nullptr;

        p_GraphicsPipeline->RenderPassDestroy(context, context->renderPass.get());
    }
}