#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLGraphicsPipeline.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    bool OpenGLGraphicsPipeline::BeginFrame(std::shared_ptr<RAPIData> apiData, _Float32 deltaTime, std::shared_ptr<PPlatformState> pState)
    {
        return p_Driver->BeginFrame(apiData, deltaTime, pState);
    }

    bool OpenGLGraphicsPipeline::EndFrame(std::shared_ptr<RAPIData> apiData, _Float32 deltaTime, std::shared_ptr<PPlatformState> pState)
    {
        return p_Driver->EndFrame(apiData, deltaTime, pState);
    }
}