#pragma once

#ifndef R_DATA_H
#define R_DATA_H

#include <cstdint>
#include <bits/floatn-common.h>

#include <PEngine/PState.h>
namespace Picasso::Engine::Render
{
    struct meshData;
    struct platformState;

    struct RenderData
    {
        _Float32 deltaTime;
    };

    struct RAPIData
    {
        EngineState* pState;
        u_int64_t frameNumber;
    };   
}

#endif