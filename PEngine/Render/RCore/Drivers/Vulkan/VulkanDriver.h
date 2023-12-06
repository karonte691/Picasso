#pragma once

#ifndef VULKAN_DRIVER_H
#define VULKAN_DRIVER_H

#include <PEngine/Render/RCore/Drivers/DriverImplementation.h>
#include <PEngine/PState.h>
#include <PEngine/Logger.h>
#include <PEngine/Render/RData.h>
#include <memory>
#include <vector>

#include <Vulkan/vulkan.h>
#if defined(_WIN32)
#include <Vulkan/vulkan_win32.h>
#elif defined(__linux__)
#include <xcb/xcb.h>
#include <Vulkan/vulkan_xcb.h>
#endif

namespace Picasso::Engine::Render::Core::Drivers
{
    struct DriverContext
    {
        VkInstance vulkanInstance;
    };

    class VulkanDriver : public DriverImplementation
    {
    public:
        bool InitDriver(std::shared_ptr<RAPIData> rcData, const char *appName, EngineState *pState) override;

    private:
        DriverContext m_context;

        VkApplicationInfo _getVkAppInfo(const char *appName);
        VkInstanceCreateInfo _getVkInstanceInfo(VkApplicationInfo *info);
        void _getVkExtensionList(std::vector<const char *> *extList);
    };
}

#endif