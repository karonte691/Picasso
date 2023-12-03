#pragma once

#ifndef P_RENDER_H
#define P_RENDER_H

#include <memory>
#include <PEngine/Logger.h>
#include <PEngine/PState.h>
#include <PEngine/Render/RData.h>
#include <PEngine/Render/RCore/RAPICore.h>

namespace Picasso::Engine::Render
{
    using Picasso::Engine::Render::Core::RAPICore;
    using Picasso::Engine::Render::RAPIData;
    using Picasso::Engine::EngineState;
    class PRender
    {
        public:
            bool Init(const char *appName, EngineState* platformState);
            bool RenderFrame(RenderData* rData);
            void OnResize(uint16_t width, uint16_t height);
            void Shutdown();
        private:
            std::unique_ptr<RAPICore> m_internalRender;
            std::shared_ptr<RAPIData> m_renderData;
    };
}

#endif