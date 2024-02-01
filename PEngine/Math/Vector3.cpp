#include <PEngine/Math/Vector3.h>
#include <cmath>

namespace Picasso::Engine::Math
{
    std::unique_ptr<Vector3> Vector3::Add(Vector3 *otherVector)
    {
        _Float32 newVectorX = x + otherVector->x;
        _Float32 newVectorY = y + otherVector->y;
        _Float32 newVectorZ = z + otherVector->z;

        return std::move(std::make_unique<Vector3>(newVectorX, newVectorY, newVectorZ));
    }

    std::unique_ptr<Vector3> Vector3::Sub(Vector3 *otherVector)
    {
        _Float32 newVectorX = x - otherVector->x;
        _Float32 newVectorY = y - otherVector->y;
        _Float32 newVectorZ = z - otherVector->z;

        return std::move(std::make_unique<Vector3>(newVectorX, newVectorY, newVectorZ));
    }

    _Float32 Vector3::Dot(Vector3 *otherVector)
    {
        _Float32 dotProduct = 0.0f;

        dotProduct += x * otherVector->x;
        dotProduct += y * otherVector->y;
        dotProduct += z * otherVector->z;

        return dotProduct;
    }

    std::unique_ptr<Vector3> Vector3::Cross(Vector3 *otherVector)
    {
        _Float32 newVectorX = z * otherVector->y - y * otherVector->z;
        _Float32 newVectorY = z * otherVector->x - x * otherVector->z;
        _Float32 newVectorZ = x * otherVector->y - y * otherVector->x;

        return std::move(std::make_unique<Vector3>(newVectorX, newVectorY, newVectorZ));
    }

    _Float32 Vector3::Distance(Vector3 *otherVector)
    {
        _Float32 newVectorX = x - otherVector->x;
        _Float32 newVectorY = y - otherVector->y;
        _Float32 newVectorZ = z - otherVector->z;

        Vector3 *vDist = new Vector3(newVectorX, newVectorY, newVectorZ);

        _Float32 sqrDistance = vDist->SqrMagnitude();

        delete vDist;

        return sqrDistance;
    }

    bool Vector3::Equals(Vector3 *otherVector, float tollerance)
    {
        if (std::abs(x - otherVector->x) > tollerance)
        {
            return false;
        }

        if (std::abs(y - otherVector->y) > tollerance)
        {
            return false;
        }

        if (std::abs(z - otherVector->z) > tollerance)
        {
            return false;
        }

        return true;
    }

    _Float32 Vector3::Magnitude()
    {
        return x * x + y * y + z * z;
    }

    _Float32 Vector3::SqrMagnitude()
    {
        return std::sqrt(this->Magnitude());
    }

    void Vector3::Normalize()
    {
        _Float32 length = this->SqrMagnitude();

        x /= length;
        y /= length;
        z /= length;
    }

    std::unique_ptr<Vector3> Vector3::Zero()
    {
        return std::move(std::make_unique<Vector3>(0.0f, 0.0f, 0.0f));
    }

    std::unique_ptr<Vector3> Vector3::Left()
    {
        return std::move(std::make_unique<Vector3>(-1.0f, 0.0f, 0.0f));
    }

    std::unique_ptr<Vector3> Vector3::Right()
    {
        return std::move(std::make_unique<Vector3>(1.0f, 0.0f, 0.0f));
    }

    std::unique_ptr<Vector3> Vector3::Up()
    {
        return std::move(std::make_unique<Vector3>(0.0f, 1.0f, 0.0f));
    }

    std::unique_ptr<Vector3> Vector3::Down()
    {
        return std::move(std::make_unique<Vector3>(0.0f, -1.0f, 0.0f));
    }

    std::unique_ptr<Vector3> Vector3::Forward()
    {
        return std::move(std::make_unique<Vector3>(0.0f, 0.0f, -1.0f));
    }

    std::unique_ptr<Vector3> Vector3::Backward()
    {
        return std::move(std::make_unique<Vector3>(0.0f, 0.0f, 1.0f));
    }
}