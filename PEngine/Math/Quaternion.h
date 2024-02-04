#pragma once

#ifndef QUATERNION_H
#define QUATERNION_H

#include <memory>

#include <PEngine/Math/Matrix.h>
#include <PEngine/Math/Vector3.h>

namespace Picasso::Engine::Math
{
    class Quaternion
    {
    public:
        float x;
        float y;
        float z;
        float w;

        Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(0.0f){};
        Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w){};

        float Normal();
        void Normalize();
        void Conjugate();
        void Inverse();
        std::unique_ptr<Quaternion> Multiply(const Quaternion *otherQuaternion);
        float Dot(const Quaternion *otherQuaternion);
        std::unique_ptr<Matrix> ToMatrix();
        std::unique_ptr<Matrix> ToRotationMatrix(const Vector3 *center);
        void Slerp(const Quaternion *otherQuaternion, float percentage);

        static std::unique_ptr<Quaternion> Identity();
        static std::unique_ptr<Quaternion> FromAxisAngle(const Vector3 *axis, float angle, bool normalize);
    };
}

#endif