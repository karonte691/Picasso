#pragma once

#ifndef VECTOR2_H
#define VECTOR2_H

#include <memory>
#include <PEngine/Math/Vector.h>

namespace Picasso::Engine::Math
{
    class Vector2 : public Vector
    {
    public:
        _Float32 x;
        _Float32 y;

        Vector2(_Float32 x, _Float32 y) : x(x), y(y){};

        std::unique_ptr<Vector2> Add(const Vector2 *otherVector);
        std::unique_ptr<Vector2> Sub(const Vector2 *otherVector);
        _Float32 Magnitude() override;
        _Float32 SqrMagnitude() override;
        _Float32 Distance(const Vector2 *otherVector);
        void Normalize() override;
        bool Equals(const Vector2 *otherVector, float tollerance);

        static std::unique_ptr<Vector2> Zero();
        static std::unique_ptr<Vector2> Left();
        static std::unique_ptr<Vector2> Right();
        static std::unique_ptr<Vector2> Up();
        static std::unique_ptr<Vector2> Down();
    };
}

#endif