#include <PEngine/Render/RCore/DriverManager.h>

// #include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDriver.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLDriver.h>

namespace Picasso::Engine::Render::Core
{
    std::unique_ptr<DriverImplementation> DriverManager::GetDriver(RDRIVERS driver)
    {
        switch (driver)
        {
        case RDRIVERS::VULKAN:
            // return std::make_unique<Picasso::Engine::Render::Core::Drivers::VulkanDriver>();
            return nullptr;
        case RDRIVERS::OPEN_GL:
            return std::make_unique<Picasso::Engine::Render::Core::Drivers::OpenGLDriver>();
        default:
            return nullptr;
        }

        return nullptr;
    }
}