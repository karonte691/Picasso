#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanPlatform.h>

#include <Vulkan/vulkan.h>
#include <xcb/xcb.h>
#include <Vulkan/vulkan_xcb.h>

namespace Picasso::Engine::Render::Core::Drivers::Vulkan
{
    std::vector<const char *> VulkanPlatform::GetPlatformExtensions()
    {
        std::vector<const char *> extList;

        extList.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
        extList.push_back(VK_KHR_XCB_SURFACE_EXTENSION_NAME);

#if PICASSO_DEBUG_ENABLE
        extList.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

        return extList;
    }

    bool VulkanPlatform::CreateSurface(std::shared_ptr<LinuxPlatformInternalState> pState, DriverContext *dContext)
    {
        if (!pState->connection || !pState->window)
        {
            Picasso::Engine::Logger::Logger::Fatal("Invalid connection or window handle");
            return false;
        }

        VkXcbSurfaceCreateInfoKHR cInfo = {VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR};

        cInfo.connection = pState->connection;
        cInfo.window = pState->window;

        VkResult result = vkCreateXcbSurfaceKHR(dContext->vulkanInstance, &cInfo, 0, &pState->surface);

        if (result != VK_SUCCESS)
        {
            Picasso::Engine::Logger::Logger::Fatal("Unable to create vulkan xcb surface");
            return false;
        }

        dContext->surface = pState->surface;

        return true;
    }

}