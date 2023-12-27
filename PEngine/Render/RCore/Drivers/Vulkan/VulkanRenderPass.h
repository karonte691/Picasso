#pragma once

#ifndef VULKAN_RENDER_PASS_H
#define VULKAN_RENDER_PASS_H

#include <memory>
#include <vector>
#include <PEngine/PState.h>
#include <PEngine/Logger/Logger.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDriverData.h>

namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
    enum VulkanRenderState
    {
        READY,
        RECORDING,
        IN_RENDER_PASS,
        SUBMITTED,
        NOT_ALLOCATED
    };

    enum VulkanCommandBufferState
    {
        COMMAND_BUFFER_STATE_READY,
        COMMAND_BUFFER_STATE_RECORDING,
        COMMAND_BUFFER_STATE_END_RECORDING,
        COMMAND_BUFFER_STATE_IN_RENDER_PASS,
        COMMAND_BUFFER_STATE_SUBMITTED,
        COMMAND_BUFFER_STATE_NOT_ALLOCATED,
    };

    struct VulkanRenderPassArea
    {
        _Float32 x;
        _Float32 y;
        _Float32 w;
        _Float32 h;

        VulkanRenderPassArea(_Float32 x = 0.0f, _Float32 y = 0.0f, _Float32 w = 0.0f, _Float32 h = 0.0f)
            : x(x), y(y), w(w), h(h) {}
    };

    struct VulkanRenderPassColor
    {
        _Float32 r;
        _Float32 g;
        _Float32 b;
        _Float32 a;

        VulkanRenderPassColor(_Float32 r = 0.0f, _Float32 g = 0.0f, _Float32 b = 0.0f, _Float32 a = 1.0f)
            : r(r), g(g), b(b), a(a) {}
    };

    struct VulkanCommandBufferDto
    {
        std::shared_ptr<VkCommandBuffer> commandBufferHandler;

        VulkanCommandBufferState state;

        VulkanCommandBufferDto(VulkanCommandBufferState initialState)
            : commandBufferHandler(std::make_shared<VkCommandBuffer>()), state(initialState) {}
    };

    struct VulkanRenderPass
    {
        std::shared_ptr<VkRenderPass> renderHandler;
        VulkanRenderPassArea area;
        VulkanRenderPassColor color;
        _Float32 depth;
        u_int32_t stencil;
        VulkanRenderState state;

        bool isValid() const
        {
            return renderHandler != nullptr && renderHandler != VK_NULL_HANDLE;
        }
    };
};

#endif