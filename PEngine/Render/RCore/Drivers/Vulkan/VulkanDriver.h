#pragma once

#ifndef VULKAN_DRIVER_H
#define VULKAN_DRIVER_H

#include <vector>
#include <PEngine/PState.h>
#include <PEngine/Logger/Logger.h>
#include <PEngine/Render/RData.h>
#include <PEngine/Render/RCore/Drivers/DriverImplementation.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDriverData.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDevice.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanPlatform.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanSwapChainManager.h>
#include <memory>

#include <Vulkan/vulkan.h>
#if defined(_WIN32)
#include <Vulkan/vulkan_win32.h>
#elif defined(__linux__)
#include <xcb/xcb.h>
#include <Vulkan/vulkan_xcb.h>
#endif

namespace Picasso::Engine::Render::Core::Drivers
{
    using Picasso::Engine::Render::Core::Drivers::Vulkan::VulkanDevice;
    using Picasso::Engine::Render::Core::Drivers::Vulkan::VulkanPlatform;
    using Picasso::Engine::Render::Core::Drivers::Vulkan::VulkanSwapChainManager;

    class VulkanDriver : public DriverImplementation
    {
    public:
        bool InitDriver(std::shared_ptr<RAPIData> rcData, const char *appName, std::shared_ptr<PPlatformState> pState, EngineState *eState) override;
        void Shutdown() override;

    private:
        DriverContext *m_context;
        VkInstance m_driverInstance;
        std::shared_ptr<VulkanDevice> m_device;
        VulkanPlatform *m_vulkanPlatform;
        VulkanSwapChainManager *m_swapChainManager;

        bool _initVulkan(const char *app_name, unsigned app_version, const std::vector<const char *> &instance_extensions);
        const char *_parseReturnError(VkResult result);
        bool _IsExtensionSupported(const char *extensionName);
    };
}

#endif