#pragma once

#ifndef VECTOR3_H
#define VECTOR3_H

#include <memory>
#include <PEngine/Math/Vector.h>

namespace Picasso::Engine::Math
{
    class Vector3 : public Vector
    {
    public:
        _Float32 x;
        _Float32 y;
        _Float32 z;

        Vector3() : x(0.0f), y(0.0f), z(0.0f){};
        Vector3(_Float32 x, _Float32 y, _Float32 z) : x(x), y(y), z(z){};

        std::unique_ptr<Vector3> Add(const Vector3 *otherVector);
        std::unique_ptr<Vector3> Sub(const Vector3 *otherVector);
        _Float32 Magnitude() override;
        _Float32 SqrMagnitude() override;
        _Float32 Distance(const Vector3 *otherVector);
        _Float32 Dot(const Vector3 *otherVector);
        std::unique_ptr<Vector3> Cross(const Vector3 *otherVector);
        void Normalize() override;
        bool Equals(const Vector3 *otherVector, float tollerance);

        static std::unique_ptr<Vector3> Zero();
        static std::unique_ptr<Vector3> Left();
        static std::unique_ptr<Vector3> Right();
        static std::unique_ptr<Vector3> Up();
        static std::unique_ptr<Vector3> Down();
        static std::unique_ptr<Vector3> Forward();
        static std::unique_ptr<Vector3> Backward();
    };
}

#endif