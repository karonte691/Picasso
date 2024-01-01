#pragma once

#ifndef VULKAN_DEBUG_H
#define VULKAN_DEBUG_H

#include <PEngine/Logger/Logger.h>

#include <Vulkan/vulkan.h>
#if defined(_WIN32)
#include <Vulkan/vulkan_win32.h>
#elif defined(__linux__)
#include <xcb/xcb.h>
#include <Vulkan/vulkan_xcb.h>
#endif

namespace Picasso::Engine::Render::Core::Drivers
{
    class VulkanDebug
    {
    public:
        static void PrintDeviceWaitError(VkResult error)
        {
            switch (error)
            {
            case VK_TIMEOUT:
                Picasso::Engine::Logger::Logger::Warn("Timed out");
                break;
            case VK_ERROR_DEVICE_LOST:
                Picasso::Engine::Logger::Logger::Warn("VK_ERROR_DEVICE_LOST.");
                break;
            case VK_ERROR_OUT_OF_HOST_MEMORY:
                Picasso::Engine::Logger::Logger::Warn("VK_ERROR_OUT_OF_HOST_MEMORY.");
                break;
            case VK_ERROR_OUT_OF_DEVICE_MEMORY:
                Picasso::Engine::Logger::Logger::Warn("VK_ERROR_OUT_OF_DEVICE_MEMORY.");
                break;
            default:
                Picasso::Engine::Logger::Logger::Warn("An unknown error has occurred.");
                break;
            }
        }
    };
}

#endif