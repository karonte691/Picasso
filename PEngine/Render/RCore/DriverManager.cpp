#include <PEngine/Render/RCore/DriverManager.h>

#include <unordered_map>
#include <PEngine/Render/RCore/Drivers/VulkanDriver.h>

namespace Picasso::Engine::Render::Core
{
    using DriverMap = std::unordered_map<RDRIVERS, std::shared_ptr<DriverImplementation>>;

    using Picasso::Engine::Render::Core::Drivers::VulkanDriver;
    
    std::shared_ptr<DriverImplementation> DriverManager::GetDriver(RDRIVERS driver)
    {
        static const DriverMap dMap = {
            {RDRIVERS::VULKAN, std::make_shared<VulkanDriver>()},
        };

        const auto& it = dMap.find(driver);
        if (it != dMap.end()) {
            return it->second;
        }

        return nullptr;
    }
}