#pragma once

#ifndef VECTOR4_H
#define VECTOR4_H

#include <memory>
#include <PEngine/Math/Vector3.h>

namespace Picasso::Engine::Math
{
    class Vector4
    {
    public:
        float x;
        float y;
        float z;
        float w;

        Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w){};

        std::unique_ptr<Vector4> Add(Vector4 *otherVector);
        std::unique_ptr<Vector4> Sub(Vector4 *otherVector);
        std::unique_ptr<Vector3> ToVector3();
        float Magnitude();
        float SqrMagnitude();
        void Normalize();
        float Dot(Vector4 *otherVector);

        static std::unique_ptr<Vector4> Zero();
        static std::unique_ptr<Vector4> FromVector3(Vector3 *v, float w);
    };
}

#endif