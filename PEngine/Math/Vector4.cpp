#include <PEngine/Math/Vector4.h>
#include <cmath>

namespace Picasso::Engine::Math
{
    std::unique_ptr<Vector4> Vector4::Add(Vector4 *otherVector)
    {
        _Float32 newVectorX = x + otherVector->x;
        _Float32 newVectorY = y + otherVector->y;
        _Float32 newVectorZ = z + otherVector->z;
        _Float32 newVectorW = z + otherVector->w;

        return std::make_unique<Vector4>(newVectorX, newVectorY, newVectorZ, newVectorW);
    }

    std::unique_ptr<Vector4> Vector4::Sub(Vector4 *otherVector)
    {
        _Float32 newVectorX = x - otherVector->x;
        _Float32 newVectorY = y - otherVector->y;
        _Float32 newVectorZ = z - otherVector->z;
        _Float32 newVectorW = z - otherVector->w;

        return std::make_unique<Vector4>(newVectorX, newVectorY, newVectorZ, newVectorW);
    }

    std::unique_ptr<Vector3> Vector4::ToVector3()
    {
        return std::make_unique<Vector3>(x, y, z);
    }

    std::unique_ptr<Vector4> Vector4::Zero()
    {
        return std::make_unique<Vector4>(0.0f, 0.0f, 0.0f, 0.0f);
    }

    std::unique_ptr<Vector4> Vector4::FromVector3(Vector3 *v, _Float32 w)
    {
        return std::make_unique<Vector4>(v->x, v->y, v->z, w);
    }
}