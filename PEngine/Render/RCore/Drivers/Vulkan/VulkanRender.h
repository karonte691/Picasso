#pragma once

#ifndef VULKAN_RENDER_H
#define VULKAN_RENDER_H

#include <PEngine/Logger/Logger.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDriverData.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanGraphicsPipeline.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanCommandBuffer.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanFrameBuffer.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanFenceManager.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanSwapChainManager.h>

namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
    class VulkanRender
    {
    public:
        VulkanRender();

        bool SetUp(DriverContext *context, u_int32_t swapChainImageCount, std::shared_ptr<PPlatformState> pState);
        void Clear(DriverContext *context);

        bool BeginRenderFrame(DriverContext *context);
        bool EndRenderFrame(DriverContext *context);
        bool RegenerateFrameBuffer(DriverContext *context, std::shared_ptr<PPlatformState> pState);
        bool RegenerateCommandBuffer(DriverContext *context);
        bool Wait(DriverContext *context);
        void CleanUpBuffers(DriverContext *context);

    private:
        VulkanGraphicsPipeline *p_GraphicsPipeline;
        VulkanCommandBuffer *p_commandBufferManager;
        VulkanFrameBuffer *p_FrameBufferManager;
        VulkanFenceManager *p_FenceManager;

        bool _decorateContext(DriverContext *context);
        bool _initFences(DriverContext *context);

        VkViewport _getViewPort(const DriverContext *context);
        VkRect2D _getScissor(const DriverContext *context);
    };
}
#endif