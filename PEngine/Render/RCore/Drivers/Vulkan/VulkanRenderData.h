#pragma once

#ifndef VULKAN_RENDER_DATA_H
#define VULKAN_RENDER_DATA_H

#include <memory>
#include <vector>
#include <PEngine/PState.h>
#include <PEngine/Logger/Logger.h>

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
        float x;
        float y;
        float w;
        float h;

        VulkanRenderPassArea(float x = 0.0f, float y = 0.0f, float w = 0.0f, float h = 0.0f)
            : x(x), y(y), w(w), h(h) {}
    };

    struct VulkanRenderPassColor
    {
        float r;
        float g;
        float b;
        float a;

        VulkanRenderPassColor(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f)
            : r(r), g(g), b(b), a(a) {}
    };

    struct VulkanCommandBufferDto
    {
        std::shared_ptr<VkCommandBuffer> commandBufferHandler = nullptr;

        VulkanCommandBufferState state;
    };

    struct VulkanFence
    {
        VkFence handler;
        bool isSignaled;
    };

    struct VulkanRenderPass
    {
        std::shared_ptr<VkRenderPass> renderHandler;
        VulkanRenderPassArea area;
        VulkanRenderPassColor color;
        float depth;
        u_int32_t stencil;
        VulkanRenderState state;

        bool isValid() const
        {
            return renderHandler != nullptr && renderHandler != VK_NULL_HANDLE;
        }
    };

    struct VulkanFrameBufferDto
    {
        VkFramebuffer handler;
        u_int32_t attachmentCount;
        std::vector<VkImageView> attachments;
        std::shared_ptr<VulkanRenderPass> renderPass;
    };
};

#endif