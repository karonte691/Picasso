#include <PEngine/Math/Vector3.h>
#include <cmath>

namespace Picasso::Engine::Math
{
    std::unique_ptr<Vector3> Vector3::Add(const Vector3 *otherVector)
    {
        float newVectorX = x + otherVector->x;
        float newVectorY = y + otherVector->y;
        float newVectorZ = z + otherVector->z;

        return std::move(std::make_unique<Vector3>(newVectorX, newVectorY, newVectorZ));
    }

    std::unique_ptr<Vector3> Vector3::Sub(const Vector3 *otherVector)
    {
        float newVectorX = x - otherVector->x;
        float newVectorY = y - otherVector->y;
        float newVectorZ = z - otherVector->z;

        return std::move(std::make_unique<Vector3>(newVectorX, newVectorY, newVectorZ));
    }

    float Vector3::Dot(const Vector3 *otherVector)
    {
        float dotProduct = 0.0f;

        dotProduct += x * otherVector->x;
        dotProduct += y * otherVector->y;
        dotProduct += z * otherVector->z;

        return dotProduct;
    }

    std::unique_ptr<Vector3> Vector3::Cross(const Vector3 *otherVector)
    {
        float newVectorX = z * otherVector->y - y * otherVector->z;
        float newVectorY = z * otherVector->x - x * otherVector->z;
        float newVectorZ = x * otherVector->y - y * otherVector->x;

        return std::move(std::make_unique<Vector3>(newVectorX, newVectorY, newVectorZ));
    }

    float Vector3::Distance(const Vector3 *otherVector)
    {
        float newVectorX = x - otherVector->x;
        float newVectorY = y - otherVector->y;
        float newVectorZ = z - otherVector->z;

        Vector3 *vDist = new Vector3(newVectorX, newVectorY, newVectorZ);

        float sqrDistance = vDist->SqrMagnitude();

        delete vDist;

        return sqrDistance;
    }

    bool Vector3::Equals(const Vector3 *otherVector, float tollerance)
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

    float Vector3::Magnitude()
    {
        return x * x + y * y + z * z;
    }

    float Vector3::SqrMagnitude()
    {
        return std::sqrt(this->Magnitude());
    }

    void Vector3::Normalize()
    {
        float length = this->SqrMagnitude();

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