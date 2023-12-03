#pragma once

#ifndef P_RENDER_H
#define P_RENDER_H

#include <PEngine/Render/RData.h>

namespace Picasso::Engine::Render
{
    class PRender
    {
        public:
            bool Init(const char *appName, platformState* platformState);
            bool RenderFrame(RenderData* rData);
            void OnResize(uint16_t width, uint16_t height);
            void Shutdown();
    };
}

#endif