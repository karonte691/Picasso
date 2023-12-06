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
        float deltaTime;
    };

    struct RAPIData
    {
        EngineState *pState;
        uint64_t frameNumber;
    };
}

#endif