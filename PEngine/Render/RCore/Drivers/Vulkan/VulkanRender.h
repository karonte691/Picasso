#pragma once

#ifndef VULKAN_RENDER_H
#define VULKAN_RENDER_H

#include <PEngine/Logger/Logger.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDriverData.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanGraphicsPipeline.h>

namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
    class VulkanRender
    {
    public:
        VulkanRender();
        ~VulkanRender();

        bool DecorateContext(DriverContext *context);
        void ClearContext(DriverContext *context);

    private:
        VulkanGraphicsPipeline *m_GraphicsPipeline;
    };
}
#endif