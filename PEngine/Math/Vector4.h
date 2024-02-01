#pragma once

#ifndef VECTOR4_H
#define VECTOR4_H

#include <memory>
#include <PEngine/Math/Vector.h>
#include <PEngine/Math/Vector3.h>

namespace Picasso::Engine::Math
{
    class Vector4 : public Vector
    {
    public:
        _Float32 x;
        _Float32 y;
        _Float32 z;
        _Float32 w;

        Vector4(_Float32 x, _Float32 y, _Float32 z, _Float32 w) : x(x), y(y), z(z), w(w){};

        std::unique_ptr<Vector4> Add(Vector4 *otherVector);
        std::unique_ptr<Vector4> Sub(Vector4 *otherVector);
        std::unique_ptr<Vector3> ToVector3();
        _Float32 Magnitude() override;
        _Float32 SqrMagnitude() override;
        void Normalize() override;
        _Float32 Dot(Vector4 *otherVector);

        static std::unique_ptr<Vector4> Zero();
        static std::unique_ptr<Vector4> FromVector3(Vector3 *v, _Float32 w);
    };
}

#endif