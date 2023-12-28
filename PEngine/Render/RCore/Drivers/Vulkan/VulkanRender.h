#pragma once

#ifndef VULKAN_RENDER_H
#define VULKAN_RENDER_H

#include <PEngine/Logger/Logger.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDriverData.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanGraphicsPipeline.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanCommandBuffer.h>

namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
    class VulkanRender
    {
    public:
        VulkanRender();

        bool SetUp(DriverContext *context, u_int32_t swapChainImageCount);
        void Clear(DriverContext *context);

    private:
        VulkanGraphicsPipeline *p_GraphicsPipeline;
        VulkanCommandBuffer *p_commandBufferManager;

        bool _decorateContext(DriverContext *context);
        void _clearContext(DriverContext *context);
    };
}
#endif