#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDriver.h>
#include <PEngine/PBuild.h>

namespace Picasso::Engine::Render::Core::Drivers
{
    bool VulkanDriver::InitDriver(std::shared_ptr<RAPIData> rcData, const char *appName, EngineState *pState)
    {
        std::vector<const char *> extensionList;

        this->_getVkExtensionList(&extensionList);

        if (!this->_initVulkan(appName, PICASSO_MAJOR_VERSION, extensionList))
        {
            Picasso::Logger::Logger::Fatal("Cannot initialize Vulkan driver...");
            return false;
        }

        return true;
    }

    bool VulkanDriver::_initVulkan(const char *app_name,
                                   unsigned app_version,
                                   const std::vector<const char *> &instance_extensions)
    {
        VkApplicationInfo vk_app_info = {};
        vk_app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        vk_app_info.pNext = nullptr;
        vk_app_info.pApplicationName = app_name;
        vk_app_info.applicationVersion = app_version;
        vk_app_info.pEngineName = app_name;
        vk_app_info.engineVersion = PICASSO_MAJOR_VERSION;
        vk_app_info.apiVersion = VK_API_VERSION_1_2;

        VkInstanceCreateInfo inst_info = {};
        inst_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        inst_info.pNext = nullptr;
        inst_info.flags = 0;
        inst_info.enabledExtensionCount = static_cast<std::uint32_t>(instance_extensions.size());
        inst_info.ppEnabledExtensionNames = &instance_extensions[0];
        inst_info.enabledLayerCount = 0;
        inst_info.ppEnabledLayerNames = 0;
        inst_info.pApplicationInfo = &vk_app_info;

        VkInstance inst;
        VkResult res = vkCreateInstance(&inst_info, 0, &inst);

        if (res != VK_SUCCESS)
        {
            const char *error = this->_parseReturnError(res);
            Picasso::Logger::Logger::FDebug("vkCreateInstance return %s", error);
        }

        return res == VK_SUCCESS;
    }

    const char *VulkanDriver::_parseReturnError(VkResult result)
    {
        switch (result)
        {
        case VK_ERROR_OUT_OF_HOST_MEMORY:
            return "OUT OF HOST MEMORY";
        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            return "OUT OF DEVICE MEMORY";
        case VK_ERROR_INITIALIZATION_FAILED:
            return "INITIALIZATION FAILED";
        case VK_ERROR_LAYER_NOT_PRESENT:
            return "LAYER NOT PRESENT";
        case VK_ERROR_EXTENSION_NOT_PRESENT:
            return "EXTENSION NOT PRESENT";
        case VK_ERROR_INCOMPATIBLE_DRIVER:
            return "INCOMPATIBLE DRIVER";
        default:
            return "UNKNOWN RESULT '" + result;
        }
    }

    void VulkanDriver::_getVkExtensionList(std::vector<const char *> *extList)
    {
        extList->push_back(VK_KHR_SURFACE_EXTENSION_NAME);

#if PICASSO_DEBUG_ENABLE
        extList->push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

#if defined(_WIN32)
        // todo
        extList->push_back(VK_KHR_WIN32_SURFACE)
#elif defined(__linux__)
        extList->push_back(VK_KHR_XCB_SURFACE_EXTENSION_NAME);
#endif
    }
}