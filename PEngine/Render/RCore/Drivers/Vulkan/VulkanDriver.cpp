#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDriver.h>
#include <PEngine/PBuild.h>

namespace Picasso::Engine::Render::Core::Drivers
{
    bool VulkanDriver::InitDriver(std::shared_ptr<RAPIData> rcData, const char *appName, std::shared_ptr<PPlatformState> pState, EngineState *eState)
    {
        m_context = new DriverContext{};
        m_vulkanPlatform = new VulkanPlatform();

        std::vector<const char *> extensionList = m_vulkanPlatform->GetPlatformExtensions();

        if (!this->_initVulkan(appName, PICASSO_MAJOR_VERSION, extensionList) || m_context->vulkanInstance == nullptr)
        {
            Picasso::Logger::Logger::Fatal("Cannot initialize Vulkan driver...");
            return false;
        }

        if (!m_vulkanPlatform->CreateSurface(pState->state, m_context))
        {
            Picasso::Logger::Logger::Fatal("Unable to create the vulkan surface...");
            return false;
        }

        m_device = new VulkanDevice();

        if (!m_device->Create(*m_context))
        {
            Picasso::Logger::Logger::Fatal("Cannot initialize Vulkan devices...");
            return false;
        }

        return true;
    }

    void VulkanDriver::Shutdown()
    {
        if (m_context != nullptr && m_context->vulkanInstance != nullptr)
        {
            Picasso::Logger::Logger::Info("Shutting down Vulkan driver...");

            vkDestroyInstance(m_context->vulkanInstance, 0);

            delete m_context;
            m_context = nullptr;
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

        for (const auto &extension : instance_extensions)
        {
            if (!this->_IsExtensionSupported(extension))
            {
                Picasso::Logger::Logger::FDebug("Required extension not supported: %s", extension);
                return false;
            }
        }

        VkResult res = vkCreateInstance(&instCreate, 0, &m_context->vulkanInstance);

        if (res != VK_SUCCESS)
        {
            const char *error = this->_parseReturnError(res);
            Picasso::Logger::Logger::FDebug("vkCreateInstance return %s", error);
        }

        return res == VK_SUCCESS;
    }

    bool VulkanDriver::_IsExtensionSupported(const char *extensionName)
    {
        uint32_t extensionCount;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        for (const auto &ext : extensions)
        {
            if (strcmp(ext.extensionName, extensionName) == 0)
            {
                return true;
            }
        }

        return false;
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