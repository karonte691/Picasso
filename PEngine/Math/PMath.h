#pragma once

#ifndef P_MATH_H
#define P_MATH_H

#include <PEngine/Math/Vector2.h>
#include <PEngine/Math/Vector3.h>
#include <PEngine/Math/Vector4.h>
#include <PEngine/Math/Quaternion.h>

namespace Picasso::Engine::Math
{
    class PMath
    {
    public:
        static float Deg2Rad(float degrees);
        static float Rad2Deg(float radians);
    };
}

#endif