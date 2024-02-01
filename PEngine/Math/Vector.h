#pragma once

#ifndef VECTOR_H
#define VECTOR_H

#include <PEngine/Math/Constants.h>
#include <bits/floatn-common.h>

namespace Picasso::Engine::Math
{
    class Vector
    {
    public:
        virtual ~Vector() = default;

        virtual _Float32 Magnitude() = 0;
        virtual _Float32 SqrMagnitude() = 0;
        virtual void Normalize() = 0;
    };
}

#endif