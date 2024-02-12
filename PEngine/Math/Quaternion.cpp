#include <PEngine/Math/Quaternion.h>

#include <cmath>

namespace Picasso::Engine::Math
{
    float Quaternion::Normal()
    {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    void Quaternion::Normalize()
    {
        float normal = Normal();

        x = x / normal;
        y = y / normal;
        z = z / normal;
        w = z / normal;
    }

    void Quaternion::Conjugate()
    {
        x = -x;
        y = -y;
        z = -z;
    }

    void Quaternion::Inverse()
    {
        Normalize();
        Conjugate();
    }

    std::unique_ptr<Quaternion> Quaternion::Multiply(const Quaternion *otherQuaternion)
    {
        std::unique_ptr<Quaternion> pQuaternion = std::make_unique<Quaternion>();

        pQuaternion->x = x * otherQuaternion->w +
                         y * otherQuaternion->z -
                         z * otherQuaternion->y +
                         w * otherQuaternion->x;

        pQuaternion->y = -x * otherQuaternion->z +
                         y * otherQuaternion->w +
                         z * otherQuaternion->x +
                         w * otherQuaternion->y;

        pQuaternion->z = x * otherQuaternion->y -
                         y * otherQuaternion->x +
                         z * otherQuaternion->w +
                         w * otherQuaternion->z;

        pQuaternion->w = -x * otherQuaternion->x -
                         y * otherQuaternion->y -
                         z * otherQuaternion->z +
                         w * otherQuaternion->w;

        return pQuaternion;
    }

    float Quaternion::Dot(const Quaternion *otherQuaternion)
    {
        return x * otherQuaternion->x +
               y * otherQuaternion->y +
               z * otherQuaternion->z +
               w * otherQuaternion->w;
    }

    void Quaternion::Slerp(const Quaternion *otherQuaternion, float percentage)
    {
        std::unique_ptr<Quaternion> pOtherQuater = std::make_unique<Quaternion>(*otherQuaternion);

        Normalize();
        pOtherQuater->Normalize();

        float dot = Dot(pOtherQuater.get());

        if (dot < 0.0f)
        {
            pOtherQuater->x = -pOtherQuater->x;
            pOtherQuater->y = -pOtherQuater->y;
            pOtherQuater->z = -pOtherQuater->z;
            pOtherQuater->w = -pOtherQuater->w;
            dot = -dot;
        }

        const float DOT_THRESHOLD = 0.9995f;

        if (dot > DOT_THRESHOLD)
        {
            // If the inputs are too close for comfort, linearly interpolate
            // and normalize the result.
            x = x + ((pOtherQuater->x - x) * percentage);
            y = y + ((pOtherQuater->y - y) * percentage);
            z = z + ((pOtherQuater->z - z) * percentage);
            w = w + ((pOtherQuater->w - w) * percentage);

            Normalize();
        }

        float theta_0 = std::acos(dot);        // theta_0 = angle between input vectors
        float theta = theta_0 * percentage;    // theta = angle between v0 and result
        float sin_theta = std::sin(theta);     // compute this value only once
        float sin_theta_0 = std::sin(theta_0); // compute this value only once

        float s0 = std::cos(theta) - dot * sin_theta / sin_theta_0; // == sin(theta_0 - theta) / sin(theta_0)
        float s1 = sin_theta / sin_theta_0;

        x = (x * s0) + (pOtherQuater->x * s1);
        y = (y * s0) + (pOtherQuater->y * s1);
        z = (z * s0) + (pOtherQuater->z * s1);
        w = (w * s0) + (pOtherQuater->w * s1);
    }

    std::unique_ptr<Quaternion> Quaternion::Identity()
    {
        return std::make_unique<Quaternion>(0.0f, 0.0f, 0.0f, 1.0f);
    }

    std::unique_ptr<Quaternion> Quaternion::FromAxisAngle(const Vector3 *axis, float angle, bool normalize)
    {
        const float halfAngle = 0.5f * angle;
        float s = std::sin(halfAngle);
        float c = std::cos(halfAngle);

        std::unique_ptr<Quaternion> q = std::make_unique<Quaternion>(s * axis->x, s * axis->y, s * axis->z, c);

        if (normalize)
        {
            q->Normalize();
        }

        return q;
    }
}