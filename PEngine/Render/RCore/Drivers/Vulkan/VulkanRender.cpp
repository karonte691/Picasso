#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanRender.h>

namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
    VulkanRender::VulkanRender()
    {
        p_GraphicsPipeline = new VulkanGraphicsPipeline();
        p_commandBufferManager = new VulkanCommandBuffer();
    }

    bool VulkanRender::SetUp(DriverContext *context, u_int32_t swapChainImageCount)
    {
        if (!p_commandBufferManager->DecorateContext(context, swapChainImageCount))
        {
            return false;
        }

        Picasso::Engine::Logger::Logger::Debug("Command pool created succesfully");

        return this->_decorateContext(context);
    }

    void VulkanRender::Clear(DriverContext *context)
    {
        p_commandBufferManager->Clear(context);

        this->_clearContext(context);
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

        context->renderPass = rpData;

        return true;
    }

    void VulkanRender::_clearContext(DriverContext *context)
    {
        context->cmBuffers->clear();
        delete context->cmBuffers;
        context->cmBuffers = nullptr;

        delete p_commandBufferManager;
        p_commandBufferManager = nullptr;

        p_GraphicsPipeline->RenderPassDestroy(context, &context->renderPass);

        delete p_GraphicsPipeline;
        p_GraphicsPipeline = nullptr;
    }
}