#include <PEngine/Render/RCore/GraphicsPipelineFactory.h>

#include <PEngine/PBuild.h>
#include <PEngine/Render/RCore/Drivers/DriverImplementation.h>
#include <unordered_map>

#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLGraphicsPipeline.h>

namespace Picasso::Engine::Render::Core
{
    using Picasso::Engine::Render::Core::Drivers::RDRIVERS;
    using DriverMap = std::unordered_map<RDRIVERS, std::shared_ptr<RGraphicsPipeline>>;
    using Picasso::Engine::Render::Core::Drivers::OpenGL::OpenGLGraphicsPipeline;

    std::shared_ptr<RGraphicsPipeline> GraphicsPipelineFactory::Get(std::shared_ptr<DriverImplementation> driver)
    {
        static const DriverMap dMap = {
            {RDRIVERS::OPEN_GL, std::make_shared<OpenGLGraphicsPipeline>(driver)},
        };

        const auto &it = dMap.find(driver->GetType());

        if (it != dMap.end())
        {
            return it->second;
        }

        return nullptr;
    }
}