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
}