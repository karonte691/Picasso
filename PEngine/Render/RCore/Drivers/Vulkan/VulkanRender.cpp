#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanRender.h>

namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
    VulkanRender::VulkanRender()
    {
        m_GraphicsPipeline = new VulkanGraphicsPipeline();
    }

    bool VulkanRender::DecorateContext(DriverContext *context)
    {
        _Float32 fbWidth = static_cast<_Float32>(context->frameBufferWidth);
        _Float32 fbHeight = static_cast<_Float32>(context->frameBufferHeight);

        VulkanRenderPassArea area = {0, 0, fbWidth, fbHeight};
        VulkanRenderPassColor color = {0.0f, 0.0f, 0.2f, 1.0f};

        VulkanRenderPass rpData = m_GraphicsPipeline->RenderPassCreate(context, area, color, 1.0f, 0);

        if (!rpData.isValid())
        {
            // render pass data is corrupted, exiting..
            Picasso::Engine::Logger::Logger::Fatal("render pass data is corrupted,");
            return false;
        }

        context->renderPass = rpData;

        return true;
    }

    void VulkanRender::ClearContext(DriverContext *context)
    {
        m_GraphicsPipeline->RenderPassDestroy(context, &context->renderPass);

        delete m_GraphicsPipeline;
        m_GraphicsPipeline = nullptr;
    }
}