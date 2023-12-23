#pragma once

#ifndef VULKAN_MEMORY_H
#define VULKAN_MEMORY_H

#include <PEngine/Logger/Logger.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDriverData.h>

namespace Picasso::Engine::Render::Core::Drivers
{
    class VulkanMemory
    {
    public:
        int32_t FindMemoryIndex(DriverContext *context, u_int32_t typeFilter, u_int32_t propertyFlags);
    };
}
#endif