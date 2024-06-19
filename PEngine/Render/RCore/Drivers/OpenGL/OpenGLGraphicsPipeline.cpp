#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLGraphicsPipeline.h>

#include <PEngine/Math/Vector3.h>
#include <PEngine/Math/PMath.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLError.h>
#include <PEngine/Render/RCore/Primitives/Quad.h>
#include <PEngine/EventSystem/DeferredEventsStore.h>
#include <PEngine/EventSystem/Events/EventTypes.h>

#include <vector>
#include <string>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    /**
     * @brief Initializes the OpenGL graphics pipeline.
     *
     * This function initializes various components of the graphics pipeline, such as the texture manager,
     * VP matrix manager, light manager, pipeline data builder, material manager, and mesh manager.
     * It also creates the view matrix and projection matrix based on the provided API data.
     * Additionally, it sets the light position and checks if the pipeline data is successfully built.
     * Finally, it sets the uniform variables for the view matrix, projection matrix, camera position, and light position.
     *
     * @param apiData A pointer to the RAPIData structure containing API data.
     * @return True if the initialization is successful, false otherwise.
     */
    bool OpenGLGraphicsPipeline::Init(RAPIData *apiData)
    {
        p_PipelineDataBuilder = std::make_unique<OpenGLPipelineDataBuilderManager>();
        p_GraphicsRender = std::make_unique<OpenGLGraphicsRender>();

        float fWidth = static_cast<float>(apiData->pState->width);
        float fHeight = static_cast<float>(apiData->pState->height);

        p_GraphicsRender->SetUp(fWidth, fHeight);

        if (!p_PipelineDataBuilder->Build())
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLGraphicsPipeline] unable to build the pipeline data");
            return false;
        }

        m_PipelineData = p_PipelineDataBuilder->Get();

        p_GraphicsRender->Uniforms(&m_PipelineData);

        return true;
    }

    void OpenGLGraphicsPipeline::Shutdown()
    {
        Picasso::Engine::EventSystem::PicassoRegistry::Unsubscribe(this, PEvent::RENDER_UPDATE_MOVEMENT);
        Picasso::Engine::EventSystem::PicassoRegistry::Unsubscribe(this, PEvent::RENDERER_UPDATE_CAMERA_POSITION);
        Picasso::Engine::EventSystem::PicassoRegistry::Unsubscribe(this, PEvent::RENDERER_UPDATE_CAMERA_VIEW);

        m_PipelineData.shader->Destroy();
    }

    void OpenGLGraphicsPipeline::RegisterHooks()
    {
        PicassoRegistry::Subscribe(this, PEvent::RENDER_UPDATE_MOVEMENT, [this](BaseEvent<PEvent> *&event)
                                   { this->_OnRenderUpdateMovement(event); });
        PicassoRegistry::Subscribe(this, PEvent::RENDERER_UPDATE_CAMERA_POSITION, [this](BaseEvent<PEvent> *&event)
                                   { this->_OnRenderUpdateCameraPosition(event); });
        PicassoRegistry::Subscribe(this, PEvent::RENDERER_UPDATE_CAMERA_VIEW, [this](BaseEvent<PEvent> *&event)
                                   { this->_OnRenderUpdateCameraView(event); });
    }

    bool OpenGLGraphicsPipeline::BeginFrame(RAPIData *apiData, float deltaTime, PPlatformState *pState)
    {
        if (!p_Driver->BeginFrame(apiData, deltaTime, pState))
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLGraphicsPipeline] driver function begin frame returned error");
            return false;
        }

        if (!p_GraphicsRender->BeginRenderFrame(&m_PipelineData))
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLGraphicsPipeline] unable to begin render frame");
            return false;
        }

        return true;
    }

    bool OpenGLGraphicsPipeline::EndFrame(RAPIData *apiData, float deltaTime, PPlatformState *pState)
    {
        p_GraphicsRender->EndRenderFrame(&m_PipelineData);

        return p_Driver->EndFrame(apiData, deltaTime, pState);
    }

    bool OpenGLGraphicsPipeline::Resize(u_int16_t width, u_int16_t height)
    {
        float fWidth = static_cast<float>(width);
        float fHeight = static_cast<float>(height);

        p_GraphicsRender->ResizeFrame(fWidth, fHeight);

        return true;
    }

    void OpenGLGraphicsPipeline::_OnRenderUpdateMovement(BaseEvent<PEvent> *&event)
    {
        EventSystem::Events::PEventData eData = event->GetData();

        float px, py, pz, rx, ry, rz, sx, sy, sz;

        px = eData.data.f[0];
        py = eData.data.f[1];
        pz = eData.data.f[2];
        rx = eData.data.f[3];
        ry = eData.data.f[4];
        rz = eData.data.f[5];
        sx = eData.data.f[6];
        sy = eData.data.f[7];
        sz = eData.data.f[8];

        p_GraphicsRender->UpdateMeshesModelMatrix(&m_PipelineData, px, py, pz, rx, ry, rz, sx, sy, sz);
    }

    void OpenGLGraphicsPipeline::_OnRenderUpdateCameraView(BaseEvent<PEvent> *&event)
    {
        p_GraphicsRender->UpdateView(&m_PipelineData);
    }

    void OpenGLGraphicsPipeline::_OnRenderUpdateCameraPosition(BaseEvent<PEvent> *&event)
    {
        p_GraphicsRender->UpdateCameraPosition(&m_PipelineData);
    }

}