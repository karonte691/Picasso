#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDriver.h>
#include <PEngine/PBuild.h>
#if PICASSO_DEBUG_ENABLE
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDebug.h>
#endif
#include <cstring>

namespace Picasso::Engine::Render::Core::Drivers
{
    bool VulkanDriver::InitDriver(std::shared_ptr<RAPIData> rcData, const char *appName, std::shared_ptr<PPlatformState> pState, EngineState *eState)
    {
        m_context = new DriverContext{};
        m_vulkanPlatform = new VulkanPlatform();

        m_context->frameBufferWidth = eState->width > 0 ? eState->width : PICASSO_DEFAULT_WIDTH;
        m_context->frameBufferHeight = eState->height > 0 ? eState->height : PICASSO_DEFAULT_HEIGHT;

        std::vector<const char *> extensionList = m_vulkanPlatform->GetPlatformExtensions();

        if (!this->_initVulkan(appName, PICASSO_MAJOR_VERSION, extensionList) || m_context->vulkanInstance == nullptr)
        {
            Picasso::Engine::Logger::Logger::Fatal("Cannot initialize Vulkan driver...");
            return false;
        }

        if (!m_vulkanPlatform->CreateSurface(pState->state, m_context))
        {
            Picasso::Engine::Logger::Logger::Fatal("Unable to create the vulkan surface...");
            return false;
        }

        m_device = std::make_shared<VulkanDevice>();

        if (!m_device->Create(m_context))
        {
            Picasso::Engine::Logger::Logger::Fatal("Cannot initialize Vulkan devices...");
            return false;
        }

        m_swapChainManager = new VulkanSwapChainManager();

        if (!m_swapChainManager->Create(m_context, eState->width, eState->height, m_device))
        {
            Picasso::Engine::Logger::Logger::Fatal("Cannot initialize Vulkan swap chain...");
            return false;
        }

        m_Render = new VulkanRender();

        if (!m_Render->SetUp(m_context, m_context->swapChain->imageCount, pState))
        {
            Picasso::Engine::Logger::Logger::Fatal("Cannot initialize Vulkan render...");
            return false;
        }

        return true;
    }

    void VulkanDriver::OnResize(u_int16_t width, u_int16_t height)
    {
        if (m_context == nullptr)
        {
            return;
        }

        m_context->frameBufferWidth = width;
        m_context->frameBufferHeight = height;
        m_context->frameBufferSizeGeneration++;

        Picasso::Engine::Logger::Logger::Debug("Resize action invoke: %d/%d generation: %d", width, height, m_context->frameBufferSizeGeneration);
    }

    bool VulkanDriver::BeginFrame(std::shared_ptr<RAPIData> apiData, _Float32 deltaTime, std::shared_ptr<PPlatformState> pState)
    {
        if (m_context == nullptr)
        {
            return false;
        }

        m_context->currentFrame = apiData->frameNumber;

        if (m_context->recreateSwapChain)
        {
            VkResult deviceWaitRes = vkDeviceWaitIdle(m_context->devices.logicalDevice);

            if (deviceWaitRes != VK_SUCCESS)
            {
#if PICASSO_DEBUG_ENABLE
                Picasso::Engine::Render::Core::Drivers::VulkanDebug::PrintDeviceWaitError(deviceWaitRes);
#endif
                return false;
            }

            Picasso::Engine::Logger::Logger::Debug("Recreating swapchain. Booting...");
            return false;
        }

        if (m_context->frameBufferSizeGeneration != m_context->frameBufferSizeLastGeneration)
        {
            // sync framebuffer
            VkResult deviceWaitRes = vkDeviceWaitIdle(m_context->devices.logicalDevice);

            if (deviceWaitRes != VK_SUCCESS)
            {
#if PICASSO_DEBUG_ENABLE
                Picasso::Engine::Render::Core::Drivers::VulkanDebug::PrintDeviceWaitError(deviceWaitRes);
#endif
                return false;
            }

            Picasso::Engine::Logger::Logger::Debug("resizing applied. Booting...");

            if (!m_swapChainManager->Recreate(m_context, m_device))
            {
                return false;
            }

            m_context->renderPass->area.w = m_context->frameBufferWidth;
            m_context->renderPass->area.h = m_context->frameBufferHeight;
            m_context->frameBufferSizeLastGeneration = m_context->frameBufferSizeGeneration;

            m_Render->CleanUpBuffers(m_context);

            m_context->renderPass->area.x = 0;
            m_context->renderPass->area.y = 0;

            if (!m_Render->RegenerateFrameBuffer(m_context, pState))
            {
                return false;
            }

            if (!m_Render->RegenerateCommandBuffer(m_context))
            {
                return false;
            }

            m_context->recreateSwapChain = false;

            return false;
        }

        if (!m_Render->Wait(m_context))
        {
            Picasso::Engine::Logger::Logger::Error("Cannot wait for fences");
            return false;
        }

        if (!m_swapChainManager->FetchNextImageIndex(m_context,
                                                     UINT64_MAX,
                                                     *m_context->imageAvailableSemaphores[m_context->currentFrame],
                                                     0))
        {
            Picasso::Engine::Logger::Logger::Error("Cannot acquire next image");
            return false;
        }

        if (!m_Render->BeginRenderFrame(m_context))
        {
            return false;
        }

        return true;
    }

    bool VulkanDriver::EndFrame(std::shared_ptr<RAPIData> apiData, _Float32 deltaTime)
    {
        if (m_context == nullptr)
        {
            return false;
        }

        if (!m_Render->EndRenderFrame(m_context))
        {
            return false;
        }

        m_swapChainManager->Present(m_context,
                                    m_context->devices.graphicsQueue,
                                    m_context->devices.presentQueue,
                                    *m_context->queueCompleteSemaphores[m_context->currentFrame]);

        return true;
    }

    void VulkanDriver::Shutdown()
    {
        if (m_context != nullptr)
        {
            Picasso::Engine::Logger::Logger::Debug("Shutting down Vulkan device data...");

            m_device->Destroy(m_context);

            if (m_Render != nullptr)
            {
                Picasso::Engine::Logger::Logger::Debug("Shutting down Vulkan Render...");

                m_Render->Clear(m_context);

                delete m_Render;
                m_Render = nullptr;
            }

            if (m_context->vulkanInstance != nullptr)
            {
                Picasso::Engine::Logger::Logger::Debug("Shutting down Vulkan driver...");

                vkDestroyInstance(m_context->vulkanInstance, 0);

                delete m_context;
                m_context = nullptr;
            }
        }

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
                Picasso::Engine::Logger::Logger::Debug("Required extension not supported: %s", extension);
                return false;
            }
        }

        VkResult res = vkCreateInstance(&instCreate, 0, &m_context->vulkanInstance);

        if (res != VK_SUCCESS)
        {
            const char *error = this->_parseReturnError(res);
            Picasso::Engine::Logger::Logger::Debug("vkCreateInstance return %s", error);
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