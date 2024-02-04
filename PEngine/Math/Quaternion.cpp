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

    std::unique_ptr<Matrix> Quaternion::ToMatrix()
    {
        std::unique_ptr<Matrix> pMatrix = Matrix::Identity();

        Normalize();

        pMatrix->data[0] = 1.0f - 2.0f * y * y - 2.0f * z * z;
        pMatrix->data[1] = 2.0f * x * y - 2.0f * z * w;
        pMatrix->data[2] = 2.0f * x * z + 2.0f * y * w;

        pMatrix->data[4] = 2.0f * x * y + 2.0f * z * w;
        pMatrix->data[5] = 1.0f - 2.0f * x * x - 2.0f * z * z;
        pMatrix->data[6] = 2.0f * y * z - 2.0f * x * w;

        pMatrix->data[8] = 2.0f * x * z - 2.0f * y * w;
        pMatrix->data[9] = 2.0f * y * z + 2.0f * x * w;
        pMatrix->data[10] = 1.0f - 2.0f * x * x - 2.0f * y * y;

        return pMatrix;
    }

    std::unique_ptr<Quaternion> Quaternion::Identity()
    {
        return std::make_unique<Quaternion>(0.0f, 0.0f, 0.0f, 1.0f);
    }

    std::unique_ptr<Matrix> Quaternion::ToRotationMatrix(const Vector3 *center)
    {
        std::unique_ptr<Matrix> pMatrix = std::make_unique<Matrix>();

        float *o = pMatrix->data;

        o[0] = (x * x) - (y * y) - (z * z) + (w * w);
        o[1] = 2.0f * ((x * y) + (z * w));
        o[2] = 2.0f * ((x * z) - (y * w));
        o[3] = center->x - center->x * o[0] - center->y * o[1] - center->z * o[2];

        o[4] = 2.0f * ((x * y) - (z * w));
        o[5] = -(x * x) + (y * y) - (z * z) + (w * w);
        o[6] = 2.0f * ((y * z) + (x * w));
        o[7] = center->y - center->x * o[4] - center->y * o[5] - center->z * o[6];

        o[8] = 2.0f * ((x * z) + (y * w));
        o[9] = 2.0f * ((y * z) - (x * w));
        o[10] = -(x * x) - (y * y) + (z * z) + (w * w);
        o[11] = center->z - center->x * o[8] - center->y * o[9] - center->z * o[10];

        o[12] = 0.0f;
        o[13] = 0.0f;
        o[14] = 0.0f;
        o[15] = 1.0f;

        return pMatrix;
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