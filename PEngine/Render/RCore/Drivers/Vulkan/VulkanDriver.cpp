#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDriver.h>
#include <PEngine/PBuild.h>

namespace Picasso::Engine::Render::Core::Drivers
{
    bool VulkanDriver::InitDriver(std::shared_ptr<RAPIData> rcData, const char *appName, EngineState *pState)
    {
        m_vulkanPlatform = new VulkanPlatform();

        std::vector<const char *> extensionList = m_vulkanPlatform->GetPlatformExtensions();

        if (!this->_initVulkan(appName, PICASSO_MAJOR_VERSION, extensionList) || m_driverInstance == nullptr)
        {
            Picasso::Logger::Logger::Fatal("Cannot initialize Vulkan driver...");
            return false;
        }

        m_device = new VulkanDevice();

        if (!m_device->Create(m_context))
        {
            Picasso::Logger::Logger::Fatal("Cannot initialize Vulkan devices...");
            return false;
        }

        return true;
    }

    void VulkanDriver::Shutdown()
    {
        if (m_driverInstance != nullptr)
        {
            Picasso::Logger::Logger::Info("Shutting down Vulkan driver...");

            vkDestroyInstance(m_driverInstance, 0);
        }

        delete m_device;
        m_device = nullptr;

        delete m_vulkanPlatform;
        m_vulkanPlatform = nullptr;
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

        VkInstanceCreateInfo instCreate = {};
        instCreate.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instCreate.pNext = nullptr;
        instCreate.flags = 0;
        instCreate.enabledExtensionCount = static_cast<std::uint32_t>(instance_extensions.size());
        instCreate.ppEnabledExtensionNames = &instance_extensions[0];
        instCreate.enabledLayerCount = 0;
        instCreate.ppEnabledLayerNames = 0;
        instCreate.pApplicationInfo = &vk_app_info;

        VkResult res = vkCreateInstance(&instCreate, 0, &m_driverInstance);

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
}