#pragma once

#ifndef VULKAN_DEVICE_H
#define VULKAN_DEVICE_H

#include <vector>
#include <PEngine/Logger/Logger.h>
#include <PEngine/PBuild.h>
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDriverData.h>

namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
    struct PhysicalDeviceRequirement
    {
        bool graphics;
        bool present;
        bool transfer;
        bool compute;

        std::vector<const char *> deviceExtensionNames;
        bool sampleAnisotropy;
        bool discreteGpu;
    };

    struct PhysicalDeviceQueueFamilyInfo
    {
        u_int32_t graphicsFamilyIndex;
        u_int32_t presentFamilyIndex;
        u_int32_t transferFamilyIndex;
        u_int32_t computeFamilyIndex;
    };

    class VulkanDevice
    {
    public:
        bool Create(DriverContext *context);
        void Destroy(DriverContext *context);

    private:
        PhysicalDeviceQueueFamilyInfo m_queueFamilyInfo;

        void _setUpDeviceQueue(DriverContext *context);
        bool _selectPhysicalDevice(DriverContext *context);
        bool _isPhysicalDeviceSupported(VkPhysicalDevice device,
                                        VkSurfaceKHR surface,
                                        const VkPhysicalDeviceProperties *pdProps,
                                        const VkPhysicalDeviceFeatures *pdFeatures,
                                        const PhysicalDeviceRequirement *requirements,
                                        SwapChainSupportInfo *swSupportInfo);
        void _getPhysicalDeviceQueueInfo(VkPhysicalDevice device, const VkPhysicalDeviceProperties *pdProps, VkSurfaceKHR surface);
        void _resetQueueFamilyInfo();
        void _querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface, SwapChainSupportInfo *swSupportInfo);
        bool _checkDeviceExtension(VkPhysicalDevice device, const PhysicalDeviceRequirement *requirements, SwapChainSupportInfo *swSupportInfo);
        void _initializeSwapChainSupportInfo(SwapChainSupportInfo &info,
                                             const std::vector<VkSurfaceFormatKHR> &availableFormats,
                                             const std::vector<VkPresentModeKHR> &availablePresentModes);
        bool _createLogicalDevice(DriverContext *context);

#if PICASSO_DEBUG_ENABLE
        void _printGpuInformation(const VkPhysicalDeviceProperties *pdProps);
#endif
    };
}

#endif