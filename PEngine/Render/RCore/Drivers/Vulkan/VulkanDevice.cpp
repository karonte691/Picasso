#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDevice.h>

#include <memory>
#include <string>
#include <cstring>

#if PICASSO_DEBUG_ENABLE
#include <iostream>
#endif
namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
    bool VulkanDevice::Create(DriverContext *context)
    {
        Picasso::Engine::Logger::Logger::Info("Selecting physical device...");
        if (!this->_selectPhysicalDevice(context))
        {
            return false;
        }

        Picasso::Engine::Logger::Logger::Info("Creating logical device...");
        if (!this->_createLogicalDevice(context))
        {
            return false;
        }

        // set up device queue
        Picasso::Engine::Logger::Logger::Info("Retrieving driver's queue");
        this->_setUpDeviceQueue(context);

        return true;
    }

    void VulkanDevice::Destroy(DriverContext *context)
    {
        context->devices.physicalDevice = 0;
        context->devices.logicalDevice = 0;

        context->devices.graphicsQueueIndex = 0;
        context->devices.presentQueueIndex = 0;
        context->devices.transferQueueIndex = 0;

        if (context->devices.swapChainSupport.formatCount > 0)
        {
            context->devices.swapChainSupport.formatCount = 0;
            context->devices.swapChainSupport.formats = 0;
        }

        if (context->devices.swapChainSupport.presentModeCount > 0)
        {
            context->devices.swapChainSupport.presentModeCount = 0;
            context->devices.swapChainSupport.presentMode = 0;
        }

        context->devices.graphicsQueueIndex = -1;
        context->devices.presentQueueIndex = -1;
        context->devices.transferQueueIndex = -1;
    }

    void VulkanDevice::QuerySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface, SwapChainSupportInfo *swSupportInfo)
    {
        VkResult gCapabilitiesResult = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &swSupportInfo->capabilities);

        if (gCapabilitiesResult != VK_SUCCESS)
        {
            Picasso::Engine::Logger::Logger::Warn("Unable to get surface capabilities for the physical device");
        }

        VkResult gFormatCountResult = vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &swSupportInfo->formatCount, 0);
        VkResult gPresentModeCountResult = vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &swSupportInfo->presentModeCount, 0);

        if (gFormatCountResult != VK_SUCCESS)
        {
            Picasso::Engine::Logger::Logger::Warn("Unable to get count surface format for the physical device");
        }

        if (gPresentModeCountResult != VK_SUCCESS)
        {
            Picasso::Engine::Logger::Logger::Warn("Unable to get count surface presents mode for the physical device");
        }

        std::vector<VkSurfaceFormatKHR> availableFormats;
        VkResult gAvailableFormatsCountResult = vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &swSupportInfo->formatCount, availableFormats.data());

        if (gAvailableFormatsCountResult != VK_SUCCESS)
        {
            Picasso::Engine::Logger::Logger::Warn("Unable to get surface format for the physical device");
        }

        std::vector<VkPresentModeKHR> availablePresentModes;
        VkResult gPresentModeResult = vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &swSupportInfo->presentModeCount, availablePresentModes.data());

        if (gPresentModeResult != VK_SUCCESS)
        {
            Picasso::Engine::Logger::Logger::Warn("Unable to get surface presents mode for the physical device");
        }

        this->_initializeSwapChainSupportInfo(*swSupportInfo, availableFormats, availablePresentModes);
    }

    bool VulkanDevice::_checkDeviceExtension(VkPhysicalDevice device, const PhysicalDeviceRequirement *requirements, SwapChainSupportInfo *swSupportInfo)
    {
        u_int32_t availableExtCount;
        VkExtensionProperties *availableExtensions;

        VkResult deviceExtensionCountResult = vkEnumerateDeviceExtensionProperties(device, nullptr, &availableExtCount, nullptr);

        if (deviceExtensionCountResult != VK_SUCCESS)
        {
            Picasso::Engine::Logger::Logger::Warn("Unable to count available extensions on this device");
            return false;
        }

        Picasso::Engine::Logger::Logger::Debug("Found %d available extensions", availableExtCount);

        if (availableExtCount > 0)
        {
            availableExtensions = new VkExtensionProperties[availableExtCount];
            VkResult deviceExtensionResult = vkEnumerateDeviceExtensionProperties(device, nullptr, &availableExtCount, availableExtensions);

            if (deviceExtensionResult != VK_SUCCESS)
            {
                Picasso::Engine::Logger::Logger::Warn("Unable to fetch available extensions on this device");
                delete[] availableExtensions;
                return false;
            }

            u_int32_t requiredExtCount = requirements->deviceExtensionNames.size();
            bool isExtFound = false;

            for (u_int32_t i = 0; i < requiredExtCount; ++i)
            {
                isExtFound = false;
                for (u_int32_t j = 0; j < availableExtCount; ++j)
                {
                    if (requirements->deviceExtensionNames[i] != nullptr && availableExtensions[j].extensionName != nullptr)
                    {
                        Picasso::Engine::Logger::Logger::Debug("Checking required extension %s", requirements->deviceExtensionNames[i]);
                        if (strcmp(requirements->deviceExtensionNames[i], availableExtensions[j].extensionName) == 0)
                        {
                            isExtFound = true;
                            break;
                        }
                    }
                }

                if (!isExtFound)
                {
                    Picasso::Engine::Logger::Logger::Debug("Required extension %s not found...", requirements->deviceExtensionNames[i]);
                    delete[] availableExtensions;
                    return false;
                }
            }

            delete[] availableExtensions;
        }

        return true;
    }

    void VulkanDevice::_setUpDeviceQueue(DriverContext *context)
    {
        vkGetDeviceQueue(context->devices.logicalDevice, context->devices.graphicsQueueIndex, 0, &context->devices.graphicsQueue);
        vkGetDeviceQueue(context->devices.logicalDevice, context->devices.presentQueueIndex, 0, &context->devices.presentQueue);
        vkGetDeviceQueue(context->devices.logicalDevice, context->devices.transferQueueIndex, 0, &context->devices.transferQueue);
    }

    bool VulkanDevice::_createLogicalDevice(DriverContext *context)
    {
        Picasso::Engine::Logger::Logger::Info("Creating logical device");

        bool presentGraphicsQueue = context->devices.graphicsQueueIndex == context->devices.presentQueueIndex;
        bool trasfertGraphicsQueue = context->devices.graphicsQueueIndex == context->devices.transferQueueIndex;
        u_int32_t indexCount = 1;

        if (!presentGraphicsQueue)
        {
            indexCount++;
        }

        if (!trasfertGraphicsQueue)
        {
            indexCount++;
        }

        std::vector<u_int32_t> logicaDevicesIndex(indexCount);

        indexCount = 0; // reusing same var for different purpose
        logicaDevicesIndex[indexCount++] = context->devices.graphicsQueueIndex;

        if (!presentGraphicsQueue)
        {
            logicaDevicesIndex[indexCount++] = context->devices.presentQueueIndex;
        }

        if (!trasfertGraphicsQueue)
        {
            logicaDevicesIndex[indexCount++] = context->devices.transferQueueIndex;
        }

        std::vector<VkDeviceQueueCreateInfo> qCreateInfo(indexCount);
        _Float32 queuePriority = 1.0f;

        for (u_int32_t i = 0; i < indexCount; ++i)
        {
            qCreateInfo[i].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            qCreateInfo[i].queueFamilyIndex = logicaDevicesIndex[i];
            qCreateInfo[i].queueCount = 1;

            if (logicaDevicesIndex[i] == context->devices.graphicsQueueIndex)
            {
                qCreateInfo[i].queueCount = 2;
            }

            qCreateInfo[i].flags = 0;
            qCreateInfo[i].pNext = 0;
            qCreateInfo[i].pQueuePriorities = &queuePriority;
        }

        VkPhysicalDeviceFeatures deviceFeatures = {};

        deviceFeatures.samplerAnisotropy = VK_TRUE;

        VkDeviceCreateInfo dCreateInfo = {VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO};
        dCreateInfo.queueCreateInfoCount = indexCount;
        dCreateInfo.pQueueCreateInfos = qCreateInfo.data();
        dCreateInfo.pEnabledFeatures = &deviceFeatures;
        dCreateInfo.enabledExtensionCount = 1;

        const char *extName = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
        dCreateInfo.ppEnabledExtensionNames = &extName;

        dCreateInfo.enabledLayerCount = 0;
        dCreateInfo.ppEnabledLayerNames = 0;

        VkResult createDeviceRes = vkCreateDevice(context->devices.physicalDevice, &dCreateInfo, 0, &context->devices.logicalDevice);

        if (createDeviceRes != VK_SUCCESS)
        {
            Picasso::Engine::Logger::Logger::Error("unable to create the logical device");
            return false;
        }

        return true;
    }

    bool VulkanDevice::_selectPhysicalDevice(DriverContext *context)
    {
        u_int32_t physicalDeviceCount = 0;

        VkResult countResult = vkEnumeratePhysicalDevices(context->vulkanInstance, &physicalDeviceCount, 0);

        if (countResult != VK_SUCCESS)
        {
            Picasso::Engine::Logger::Logger::Error("Cannot count physical devices...");
            return false;
        }

        if (physicalDeviceCount == 0)
        {
            Picasso::Engine::Logger::Logger::Error("No physical devices found...");
            return false;
        }

        std::vector<VkPhysicalDevice> detectedDevices(physicalDeviceCount);

        VkResult fetchPhysicalDevicesRes = vkEnumeratePhysicalDevices(context->vulkanInstance, &physicalDeviceCount, detectedDevices.data());

        if (fetchPhysicalDevicesRes != VK_SUCCESS)
        {
            Picasso::Engine::Logger::Logger::Error("Cannot fetch physical devices...");
            return false;
        }

        VkPhysicalDeviceProperties pdProps;
        VkPhysicalDeviceFeatures pdFeatures;
        VkPhysicalDeviceMemoryProperties pdMemoryProps;

        PhysicalDeviceRequirement pDeviceRequirements;
        pDeviceRequirements.graphics = true;
        pDeviceRequirements.compute = true;
        pDeviceRequirements.present = true;
        pDeviceRequirements.transfer = true;
        pDeviceRequirements.discreteGpu = false;
        pDeviceRequirements.sampleAnisotropy = true;

        pDeviceRequirements.deviceExtensionNames.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

        m_queueFamilyInfo = {};
        bool deviceMeetReqs = false;

        for (u_int32_t i = 0; i < physicalDeviceCount; ++i)
        {
            vkGetPhysicalDeviceProperties(detectedDevices[i], &pdProps);
            vkGetPhysicalDeviceFeatures(detectedDevices[i], &pdFeatures);
            vkGetPhysicalDeviceMemoryProperties(detectedDevices[i], &pdMemoryProps);

            deviceMeetReqs = this->_isPhysicalDeviceSupported(
                detectedDevices[i],
                context->surface,
                &pdProps,
                &pdFeatures,
                &pDeviceRequirements,
                &context->devices.swapChainSupport);

            if (!deviceMeetReqs)
            {
                continue;
            }

            Picasso::Engine::Logger::Logger::Debug("Selected device %s", pdProps.deviceName);

#if PICASSO_DEBUG_ENABLE
            this->_printGpuInformation(&pdProps);
#endif
            Picasso::Engine::Logger::Logger::Debug("GPU Driver version %d.%d.%d",
                                                   VK_VERSION_MAJOR(pdProps.driverVersion),
                                                   VK_VERSION_MINOR(pdProps.driverVersion),
                                                   VK_VERSION_PATCH(pdProps.driverVersion));

            Picasso::Engine::Logger::Logger::Debug("Vulkan API Version %d.%d.%d",
                                                   VK_VERSION_MAJOR(pdProps.apiVersion),
                                                   VK_VERSION_MINOR(pdProps.apiVersion),
                                                   VK_VERSION_PATCH(pdProps.apiVersion));

            context->devices.physicalDevice = detectedDevices[i];
            context->devices.graphicsQueueIndex = m_queueFamilyInfo.graphicsFamilyIndex;
            context->devices.presentQueueIndex = m_queueFamilyInfo.presentFamilyIndex;
            context->devices.transferQueueIndex = m_queueFamilyInfo.transferFamilyIndex;

            context->devices.properties = pdProps;
            context->devices.features = pdFeatures;
            context->devices.memoryProperties = pdMemoryProps;

            break;
        }

        if (!context->devices.physicalDevice)
        {
            Picasso::Engine::Logger::Logger::Error("Unable to select a physical device");
            return false;
        }
        return true;
    }

    bool VulkanDevice::_isPhysicalDeviceSupported(
        VkPhysicalDevice device,
        VkSurfaceKHR surface,
        const VkPhysicalDeviceProperties *pdProps,
        const VkPhysicalDeviceFeatures *pdFeatures,
        const PhysicalDeviceRequirement *requirements,
        SwapChainSupportInfo *swSupportInfo)
    {
        this->_resetQueueFamilyInfo();

        if (requirements->discreteGpu)
        {
            if (pdProps->deviceType != VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            {
                Picasso::Engine::Logger::Logger::Error("Picasso requires discreteGpu, but the device does not support it");
                return false;
            }
        }

        this->_getPhysicalDeviceQueueInfo(device, pdProps, surface);

        if (
            // Check graphics queue requirements
            (!requirements->graphics || (requirements->graphics && m_queueFamilyInfo.graphicsFamilyIndex != -1)) &&

            // Check presentation queue requirements
            (!requirements->present || (requirements->present && m_queueFamilyInfo.presentFamilyIndex != -1)) &&

            // Check compute queue requirements
            (!requirements->compute || (requirements->compute && m_queueFamilyInfo.computeFamilyIndex != -1)) &&

            // Check transfer queue requirements
            (!requirements->transfer || (requirements->transfer && m_queueFamilyInfo.transferFamilyIndex != -1)))
        {
            Picasso::Engine::Logger::Logger::Debug("Device %s meets the requirement", pdProps->deviceName);

            this->QuerySwapChainSupport(device, surface, swSupportInfo);

            if (swSupportInfo->formatCount < 1 || swSupportInfo->presentModeCount < 1)
            {
                Picasso::Engine::Logger::Logger::Error("Required swapchain support not present, skipping device...");
                return false;
            }

            if (!this->_checkDeviceExtension(device, requirements, swSupportInfo))
            {
                Picasso::Engine::Logger::Logger::Error("Unable to check the extensions, skipping device...");
                return false;
            }

            if (requirements->sampleAnisotropy && !pdFeatures->samplerAnisotropy)
            {
                Picasso::Engine::Logger::Logger::Error("sampleAnisotropy is not compatible, skipping device...");
                return false;
            }

            return true;
        }

        return false;
    }

    void VulkanDevice::_getPhysicalDeviceQueueInfo(VkPhysicalDevice device, const VkPhysicalDeviceProperties *pdProps, VkSurfaceKHR surface)
    {
        u_int32_t queueFamilyInfoCount;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyInfoCount, 0);

        if (queueFamilyInfoCount == 0)
        {
            return;
        }

        std::vector<VkQueueFamilyProperties> queueFamilyProps(queueFamilyInfoCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyInfoCount, queueFamilyProps.data());

        u_int8_t cTransferScore = 0;
        u_int8_t minTransferScore = PICASSO_VULKAN_MIN_TRANSFER_SCORE;
        VkBool32 supportPresent = false;
        VkResult supportPresentResult = VK_ERROR_DEVICE_LOST; // random error, just for reset

        for (u_int32_t i = 0; i < queueFamilyInfoCount; ++i)
        {
            if (queueFamilyProps[i].queueFlags && VK_QUEUE_GRAPHICS_BIT)
            {
                m_queueFamilyInfo.graphicsFamilyIndex = i;
                ++cTransferScore;
            }

            if (queueFamilyProps[i].queueFlags && VK_QUEUE_COMPUTE_BIT)
            {
                m_queueFamilyInfo.computeFamilyIndex = i;
                ++cTransferScore;
            }

            if (queueFamilyProps[i].queueFlags && VK_QUEUE_TRANSFER_BIT)
            {
                if (cTransferScore <= minTransferScore)
                {
                    minTransferScore = cTransferScore;
                    m_queueFamilyInfo.transferFamilyIndex = i;
                }
            }

            supportPresentResult = VK_ERROR_DEVICE_LOST; // again, random error, just for reset
            supportPresentResult = vkGetPhysicalDeviceSurfaceSupportKHR(device, 1, surface, &supportPresent);

            if (supportPresentResult != VK_SUCCESS)
            {
                Picasso::Engine::Logger::Logger::Warn("Unable to check if the physical device supports surface");
                continue;
            }

            if (supportPresent)
            {
                m_queueFamilyInfo.presentFamilyIndex = i;
            }
        }
    }

    void VulkanDevice::_resetQueueFamilyInfo()
    {
        m_queueFamilyInfo.graphicsFamilyIndex = -1;
        m_queueFamilyInfo.computeFamilyIndex = -1;
        m_queueFamilyInfo.presentFamilyIndex = -1;
        m_queueFamilyInfo.transferFamilyIndex = -1;
    }

        void VulkanDevice::_initializeSwapChainSupportInfo(SwapChainSupportInfo &info,
                                                       const std::vector<VkSurfaceFormatKHR> &availableFormats,
                                                       const std::vector<VkPresentModeKHR> &availablePresentModes)
    {
        if (info.formatCount > 0 && availableFormats.size() >= info.formatCount)
        {
            info.formats = std::make_unique<VkSurfaceFormatKHR[]>(info.formatCount);
            for (size_t i = 0; i < info.formatCount; ++i)
            {
                info.formats[i] = availableFormats[i];
            }
        }

        if (info.presentModeCount > 0 && availablePresentModes.size() >= info.presentModeCount)
        {
            info.presentMode = std::make_unique<VkPresentModeKHR[]>(info.presentModeCount);
            for (size_t i = 0; i < info.presentModeCount; ++i)
            {
                info.presentMode[i] = availablePresentModes[i];
            }
        }
    }

#if PICASSO_DEBUG_ENABLE

    void VulkanDevice::_printGpuInformation(const VkPhysicalDeviceProperties *pdProps)
    {
        const char *gpuDeviceType;

        switch (pdProps->deviceType)
        {
        default:
        case VK_PHYSICAL_DEVICE_TYPE_OTHER:
            gpuDeviceType = "GPU type is Unknown.";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
            gpuDeviceType = "GPU type is Integrated.";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
            gpuDeviceType = "GPU type is Descrete.";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
            gpuDeviceType = "GPU type is Virtual.";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_CPU:
            gpuDeviceType = "GPU type is CPU.";
            break;
        }

        Picasso::Engine::Logger::Logger::Info(gpuDeviceType);
    }
#endif
}