#pragma once

#ifndef VULKAN_RENDER_H
#define VULKAN_RENDER_H

#include <PEngine/Logger/Logger.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDriverData.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanGraphicsPipeline.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanCommandBuffer.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanFrameBuffer.h>

namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
    class VulkanRender
    {
    public:
        VulkanRender();

        bool SetUp(DriverContext *context, u_int32_t swapChainImageCount, std::shared_ptr<PPlatformState> pState);
        void Clear(DriverContext *context);

    private:
        VulkanGraphicsPipeline *p_GraphicsPipeline;
        VulkanCommandBuffer *p_commandBufferManager;
        VulkanFrameBuffer *p_FrameBufferManager;

        bool _decorateContext(DriverContext *context);
        bool _regenerateFrameBuffer(DriverContext *context, std::shared_ptr<PPlatformState> pState);
        void _clearContext(DriverContext *context);
    };
}
#endif