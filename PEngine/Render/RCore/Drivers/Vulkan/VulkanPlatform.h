#pragma once

#ifndef VULKAN_PLATFORM_H
#define VULKAN_PLATFORM_H

#include <memory>
#include <vector>
#include <PEngine/PState.h>
#include <PEngine/Logger.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDriverData.h>
#include <PEngine/Platform/Linux/LinuxPlatformInternalState.h>

namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
#ifdef PICASSO_LINUX_BUILD
    using Picasso::Engine::Platform::LinuxPlatformInternalState;
#endif

    class VulkanPlatform
    {
    public:
        std::vector<const char *> GetPlatformExtensions();

#ifdef PICASSO_LINUX_BUILD
        bool CreateSurface(std::shared_ptr<LinuxPlatformInternalState> pState, DriverContext *dContext);
#endif
    };
}

#endif
