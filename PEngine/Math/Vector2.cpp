#include <PEngine/Math/Vector2.h>
#include <cmath>

namespace Picasso::Engine::Math
{
    std::shared_ptr<Vector2> Vector2::Add(std::shared_ptr<Vector2> otherVector)
    {
        _Float32 newVectorX = x + otherVector->x;
        _Float32 newVectorY = y + otherVector->y;

        return std::make_shared<Vector2>(newVectorX, newVectorY);
    }

    std::shared_ptr<Vector2> Vector2::Sub(std::shared_ptr<Vector2> otherVector)
    {
        _Float32 newVectorX = x - otherVector->x;
        _Float32 newVectorY = y - otherVector->y;

        return std::make_shared<Vector2>(newVectorX, newVectorY);
    }

    _Float32 Vector2::Magnitude()
    {
        return x * x + y * y;
    }

    _Float32 Vector2::SqrMagnitude()
    {
        return std::sqrt(this->Magnitude());
    }

    void Vector2::Normalize()
    {
        _Float32 length = this->SqrMagnitude();

        x /= length;
        y /= length;
    }

    bool Vector2::Equals(std::shared_ptr<Vector2> otherVector, float tollerance)
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

    /**
     *  STATIC FUNCTIONS
     */
    std::shared_ptr<Vector2> Vector2::Zero()
    {
        return std::make_shared<Vector2>(0.0f, 0.0f);
    }

    std::shared_ptr<Vector2> Vector2::Left()
    {
        return std::make_shared<Vector2>(-1.0f, 0.0f);
    }

    std::shared_ptr<Vector2> Vector2::Right()
    {
        return std::make_shared<Vector2>(1.0f, 0.0f);
    }

    std::shared_ptr<Vector2> Vector2::Up()
    {
        return std::make_shared<Vector2>(0.0f, 1.0f);
    }

    std::shared_ptr<Vector2> Vector2::Down()
    {
        return std::make_shared<Vector2>(0.0f, -1.0f);
    }
}