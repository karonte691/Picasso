#pragma once

#ifndef VECTOR2_H
#define VECTOR2_H

namespace Picasso::Engine::Math
{
    class Vector2
    {
    public:
        float x;
        float y;

        Vector2() : x(0.0f), y(0.0f) {}
        Vector2(float x, float y) : x(x), y(y){};

        Vector2 Add(const Vector2 *otherVector);
        Vector2 Sub(const Vector2 *otherVector);
        float Magnitude();
        float SqrMagnitude();
        float Distance(const Vector2 *otherVector);
        void Normalize();
        bool Equals(const Vector2 *otherVector, float tollerance);

        static Vector2 Zero();
        static Vector2 Left();
        static Vector2 Right();
        static Vector2 Up();
        static Vector2 Down();
    };
}

#endif