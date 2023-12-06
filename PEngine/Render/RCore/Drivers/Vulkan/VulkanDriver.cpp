#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDriver.h>
#include <PEngine/PBuild.h>

namespace Picasso::Engine::Render::Core::Drivers
{
    bool VulkanDriver::InitDriver(std::shared_ptr<RAPIData> rcData, const char *appName, EngineState *pState)
    {
        m_context = {VK_NULL_HANDLE};

        if (!rcData || !appName || !pState)
        {
            Picasso::Logger::Logger::Fatal("Invalid input parameters.");
            return false;
        }

        VkApplicationInfo vkAppInfo = this->_getVkAppInfo(appName);
        VkInstanceCreateInfo vkInstanceInfo = this->_getVkInstanceInfo(&vkAppInfo);

        if (vkInstanceInfo.sType != VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO)
        {
            Picasso::Logger::Logger::Fatal("VkInstanceCreateInfo is not initialized correctly.");
            return false;
        }

        VkResult instanceCreateResult = vkCreateInstance(&vkInstanceInfo, nullptr, &m_context.vulkanInstance);

        if (instanceCreateResult != VK_SUCCESS)
        {
            Picasso::Logger::Logger::FDebug("vkCreateInstance returned a non-success code: %d", instanceCreateResult);
            return false;
        }

        if (m_context.vulkanInstance == VK_NULL_HANDLE)
        {
            Picasso::Logger::Logger::Fatal("Vulkan instance is null after initialization.");
            return false;
        }

        return true;
    }

    VkApplicationInfo VulkanDriver::_getVkAppInfo(const char *appName)
    {
        VkApplicationInfo vkApplicationInfo = {VK_STRUCTURE_TYPE_APPLICATION_INFO};

        vkApplicationInfo.apiVersion = VK_API_VERSION_1_2;
        vkApplicationInfo.pApplicationName = appName;
        vkApplicationInfo.applicationVersion = VK_MAKE_VERSION(PICASSO_MAJOR_VERSION, PICASSO_MINOR_VERSION, PICASSO_PATCH_VERSION);
        vkApplicationInfo.pEngineName = "Picasso";
        vkApplicationInfo.engineVersion = VK_MAKE_VERSION(PICASSO_MAJOR_VERSION, PICASSO_MINOR_VERSION, PICASSO_PATCH_VERSION);

        return vkApplicationInfo;
    }

    VkInstanceCreateInfo VulkanDriver::_getVkInstanceInfo(VkApplicationInfo *info)
    {
        std::vector<const char *> extensionList;

        this->_getVkExtensionList(&extensionList);

        VkInstanceCreateInfo vkInfo = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
        vkInfo.enabledExtensionCount = extensionList.size();
        vkInfo.pApplicationInfo = info;
        vkInfo.ppEnabledExtensionNames = extensionList.data();
        vkInfo.enabledLayerCount = 0;
        vkInfo.ppEnabledLayerNames = 0;

        return vkInfo;
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