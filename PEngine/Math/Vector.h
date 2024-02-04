#pragma once

#ifndef VECTOR_H
#define VECTOR_H

#include <PEngine/Math/Constants.h>

namespace Picasso::Engine::Math
{
    class Vector
    {
    public:
        virtual ~Vector(){};

        virtual float Magnitude() = 0;
        virtual float SqrMagnitude() = 0;
        virtual void Normalize() = 0;
    };
}

#endif