#pragma once

#ifndef VECTOR2_H
#define VECTOR2_H

#include <memory>
#include <PEngine/Math/Vector.h>
#include <bits/floatn-common.h>

namespace Picasso::Engine::Math
{
    class Vector2 : public Vector
    {
    public:
        _Float32 x;
        _Float32 y;

        Vector2(_Float32 x, _Float32 y) : x(x), y(y){};

        std::shared_ptr<Vector2> Add(std::shared_ptr<Vector2> otherVector);
        std::shared_ptr<Vector2> Sub(std::shared_ptr<Vector2> otherVector);
        _Float32 Magnitude();
        _Float32 SqrMagnitude();
        _Float32 Distance(std::shared_ptr<Vector2> otherVector);
        void Normalize();
        bool Equals(std::shared_ptr<Vector2> otherVector, float tollerance);

        static std::shared_ptr<Vector2> Zero();
        static std::shared_ptr<Vector2> Left();
        static std::shared_ptr<Vector2> Right();
        static std::shared_ptr<Vector2> Up();
        static std::shared_ptr<Vector2> Down();
    };
}

#endif