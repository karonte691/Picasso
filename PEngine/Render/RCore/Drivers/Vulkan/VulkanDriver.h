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
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanRender.h>
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
    using Picasso::Engine::Render::Core::Drivers::Vulkan::VulkanRender;
    using Picasso::Engine::Render::Core::Drivers::Vulkan::VulkanSwapChainManager;

    class VulkanDriver : public DriverImplementation
    {
    public:
        bool InitDriver(std::shared_ptr<RAPIData> rcData, const char *appName, std::shared_ptr<PPlatformState> pState, EngineState *eState) override;
        void OnResize(u_int16_t width, u_int16_t height) override;
        bool BeginFrame(std::shared_ptr<RAPIData> apiData, _Float32 deltaTime, std::shared_ptr<PPlatformState> pState) override;
        bool EndFrame(std::shared_ptr<RAPIData> apiData, _Float32 deltaTime) override;
        void Shutdown() override;

    private:
        DriverContext *m_context;
        VkInstance m_driverInstance;
        std::shared_ptr<VulkanDevice> m_device;
        VulkanPlatform *m_vulkanPlatform;
        VulkanSwapChainManager *m_swapChainManager;
        VulkanRender *m_Render;

        bool _initVulkan(const char *app_name, unsigned app_version, const std::vector<const char *> &instance_extensions);
        const char *_parseReturnError(VkResult result);
        bool _IsExtensionSupported(const char *extensionName);
    };
}

#endif