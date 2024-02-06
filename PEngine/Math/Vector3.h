#pragma once

#ifndef VECTOR3_H
#define VECTOR3_H

namespace Picasso::Engine::Math
{
    class Vector3
    {
    public:
        float x;
        float y;
        float z;

        Vector3() : x(0.0f), y(0.0f), z(0.0f){};
        Vector3(float x, float y, float z) : x(x), y(y), z(z){};

        Vector3 Add(const Vector3 *otherVector);
        Vector3 Sub(const Vector3 *otherVector);
        float Magnitude();
        float SqrMagnitude();
        float Distance(const Vector3 *otherVector);
        float Dot(const Vector3 *otherVector);
        Vector3 Cross(const Vector3 *otherVector);
        void Normalize();
        bool Equals(const Vector3 *otherVector, float tollerance);

        static Vector3 Zero();
        static Vector3 Left();
        static Vector3 Right();
        static Vector3 Up();
        static Vector3 Down();
        static Vector3 Forward();
        static Vector3 Backward();
    };
}

#endif