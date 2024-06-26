#include <PEngine/Math/Vector2.h>
#include <cmath>

namespace Picasso::Engine::Math
{
    Vector2 Vector2::Add(const Vector2 *otherVector)
    {
        float newVectorX = x + otherVector->x;
        float newVectorY = y + otherVector->y;

        return Vector2{newVectorX, newVectorY};
    }

    Vector2 Vector2::Sub(const Vector2 *otherVector)
    {
        float newVectorX = x - otherVector->x;
        float newVectorY = y - otherVector->y;

        return Vector2{newVectorX, newVectorY};
    }

    float Vector2::Magnitude()
    {
        return x * x + y * y;
    }

    float Vector2::SqrMagnitude()
    {
        return std::sqrt(this->Magnitude());
    }

    void Vector2::Normalize()
    {
        float length = this->SqrMagnitude();

        x /= length;
        y /= length;
    }

    bool Vector2::Equals(const Vector2 *otherVector, float tollerance)
    {
        if (std::abs(x - otherVector->x) > tollerance)
        {
            return false;
        }

        if (std::abs(y - otherVector->y) > tollerance)
        {
            return false;
        }

        return true;
    }

    float Vector2::Distance(const Vector2 *otherVector)
    {
        float newVectorX = x - otherVector->x;
        float newVectorY = y - otherVector->y;

        Vector2 *vDist = new Vector2(newVectorX, newVectorY);

        float sqrDistance = vDist->SqrMagnitude();

        delete vDist;

        return sqrDistance;
    }

    /**
     *  STATIC FUNCTIONS
     */
    Vector2 Vector2::Zero()
    {
        return Vector2{0.0f, 0.0f};
    }

    Vector2 Vector2::Left()
    {
        return Vector2{-1.0f, 0.0f};
    }

    Vector2 Vector2::Right()
    {
        return Vector2{1.0f, 0.0f};
    }

    Vector2 Vector2::Up()
    {
        return Vector2{0.0f, 1.0f};
    }

    Vector2 Vector2::Down()
    {
        return Vector2{0.0f, -1.0f};
    }
}