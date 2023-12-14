#pragma once

#ifndef P_RENDER_H
#define P_RENDER_H

#include <memory>
#include <PEngine/Logger/Logger.h>
#include <PEngine/PState.h>
#include <PEngine/Render/RData.h>
#include <PEngine/Render/RCore/RAPICore.h>

namespace Picasso::Engine::Render
{
    using Picasso::Engine::EngineState;
    using Picasso::Engine::Render::RAPIData;
    using Picasso::Engine::Render::Core::RAPICore;
    class PRender
    {
    public:
        bool Init(const char *appName, std::shared_ptr<PPlatformState> pState, EngineState *engineState);
        bool RenderFrame(RenderData *rData);
        void OnResize(uint16_t width, uint16_t height);
        void Shutdown();

    private:
        std::unique_ptr<RAPICore> m_internalRender;
        std::shared_ptr<RAPIData> m_renderData;
    };
}

#endif