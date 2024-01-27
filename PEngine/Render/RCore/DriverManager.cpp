#include <PEngine/Render/RCore/DriverManager.h>

#if PICASSO_VULKAN_BUILD
#include <PEngine/Render/RCore/Drivers/Vulkan/VulkanDriver.h>
#elif PICASSO_OPENGL_BUILD
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLDriver.h>
#endif

#include <PEngine/PBuild.h>

namespace Picasso::Engine::Render::Core
{

    std::shared_ptr<DriverImplementation> DriverManager::GetDriver(RDRIVERS driver)
    {
        switch (driver)
        {
        case RDRIVERS::VULKAN:
#if PICASSO_VULKAN_BUILD
            return std::make_shared<Picasso::Engine::Render::Core::Drivers::VulkanDriver>();
#else
            return nullptr;
#endif
        case RDRIVERS::OPEN_GL:
#if PICASSO_OPENGL_BUILD
            return std::make_shared<Picasso::Engine::Render::Core::Drivers::OpenGLDriver>();
#else
            return nullptr;
#endif
        default:
            return nullptr;
        }

        return nullptr;
    }
}