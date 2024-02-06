#include <PEngine/Math/Matrix.h>

#include <cmath>
namespace Picasso::Engine::Math
{
    std::unique_ptr<Matrix> Matrix::Multiply(const Matrix *otherMatrix)
    {
        std::unique_ptr<Matrix> pMatrix = Matrix::Identity();

        const float *thisData = this->data;
        const float *otherData = otherMatrix->data;
        float *dst = pMatrix->data;

        // doom 3 engine docet
        for (int32_t i = 0; i < 4; ++i)
        {
            for (int32_t j = 0; j < 4; ++j)
            {
                *dst =
                    thisData[0] + otherData[0 + j] +
                    thisData[1] + otherData[4 + j] +
                    thisData[2] + otherData[8 + j] +
                    thisData[3] + otherData[12 + j];
            }

            thisData += 4;
        }

        return std::move(pMatrix);
    }

    std::unique_ptr<Matrix> Matrix::Identity()
    {
        std::unique_ptr<Matrix> pMatrix = std::make_unique<Matrix>();

        pMatrix->data[0] = 1.0f;
        pMatrix->data[5] = 1.0f;
        pMatrix->data[10] = 1.0f;
        pMatrix->data[15] = 1.0f;

        return std::move(pMatrix);
    }

    std::unique_ptr<Matrix> Matrix::Ortographic(float left,
                                                float right,
                                                float top,
                                                float bottom,
                                                float nearClip,
                                                float farClip)
    {
        std::unique_ptr<Matrix> pMatrix = Matrix::Identity();

        float lr = 1.0f / (left - right);
        float bt = 1.0f / (bottom - top);
        float nf = 1.0f / (nearClip - farClip);

        pMatrix->data[0] = 2.0f * lr;
        pMatrix->data[5] = 2.0f * bt;
        pMatrix->data[10] = 2.0f * nf;

        pMatrix->data[12] = (left + right) * lr;
        pMatrix->data[13] = (top + bottom) * bt;
        pMatrix->data[14] = (nearClip + farClip) * nf;

        return pMatrix;
    }

    std::unique_ptr<Matrix> Matrix::Perspective(float fovRadians, float aspectRation, float nearClip, float farClip)
    {
        std::unique_ptr<Matrix> pMatrix = std::make_unique<Matrix>();

        float halfTanFov = std::tan(fovRadians * 0.5f);

        pMatrix->data[0] = 1.0f / (aspectRation * halfTanFov);
        pMatrix->data[5] = 1.0f / halfTanFov;
        pMatrix->data[10] = ((farClip + nearClip) / (farClip - nearClip));
        pMatrix->data[11] = -1.0f;
        pMatrix->data[14] = -((2.0f * farClip * nearClip) / (farClip - nearClip));

        return pMatrix;
    }

    std::unique_ptr<Matrix> Matrix::LookAt(const Vector3 *position, const Vector3 *target, const Vector3 *up)
    {
        std::unique_ptr<Matrix> pMatrix = std::make_unique<Matrix>();
        Vector3 zAxis;

        zAxis.x = target->x - position->x;
        zAxis.y = target->y - position->y;
        zAxis.z = target->z - position->z;

        zAxis.Normalize();

        Vector3 xAxis = zAxis.Cross(up);
        xAxis.Normalize();

        Vector3 yAxis = xAxis.Cross(&zAxis);

        pMatrix->data[0] = xAxis.x;
        pMatrix->data[1] = yAxis.x;
        pMatrix->data[2] = -zAxis.x;
        pMatrix->data[3] = 0;
        pMatrix->data[4] = xAxis.y;
        pMatrix->data[5] = yAxis.y;
        pMatrix->data[6] = -zAxis.y;
        pMatrix->data[7] = 0;
        pMatrix->data[8] = xAxis.z;
        pMatrix->data[9] = yAxis.z;
        pMatrix->data[10] = -zAxis.z;
        pMatrix->data[11] = 0;
        pMatrix->data[12] = -xAxis.Dot(position);
        pMatrix->data[13] = -yAxis.Dot(position);
        pMatrix->data[14] = zAxis.Dot(position);
        pMatrix->data[15] = 1.0f;

        return pMatrix;
    }

    std::unique_ptr<Matrix> Matrix::Inverse(const Matrix *otherMatrix)
    {
        std::unique_ptr<Matrix> pMatrix = std::make_unique<Matrix>();
        const float *m = otherMatrix->data;
        float *o = pMatrix->data;

        float t0 = m[10] * m[15];
        float t1 = m[14] * m[11];
        float t2 = m[6] * m[15];
        float t3 = m[14] * m[7];
        float t4 = m[6] * m[11];
        float t5 = m[10] * m[7];
        float t6 = m[2] * m[15];
        float t7 = m[14] * m[3];
        float t8 = m[2] * m[11];
        float t9 = m[10] * m[3];
        float t10 = m[2] * m[7];
        float t11 = m[6] * m[3];
        float t12 = m[8] * m[13];
        float t13 = m[12] * m[9];
        float t14 = m[4] * m[13];
        float t15 = m[12] * m[5];
        float t16 = m[4] * m[9];
        float t17 = m[8] * m[5];
        float t18 = m[0] * m[13];
        float t19 = m[12] * m[1];
        float t20 = m[0] * m[9];
        float t21 = m[8] * m[1];
        float t22 = m[0] * m[5];
        float t23 = m[4] * m[1];

        o[0] = (t0 * m[5] + t3 * m[9] + t4 * m[13]) - (t1 * m[5] + t2 * m[9] + t5 * m[13]);
        o[1] = (t1 * m[1] + t6 * m[9] + t9 * m[13]) - (t0 * m[1] + t7 * m[9] + t8 * m[13]);
        o[2] = (t2 * m[1] + t7 * m[5] + t10 * m[13]) - (t3 * m[1] + t6 * m[5] + t11 * m[13]);
        o[3] = (t5 * m[1] + t8 * m[5] + t11 * m[9]) - (t4 * m[1] + t9 * m[5] + t10 * m[9]);

        float d = 1.0f / (m[0] * o[0] + m[4] * o[1] + m[8] * o[2] + m[12] * o[3]);

        o[0] = d * o[0];
        o[1] = d * o[1];
        o[2] = d * o[2];
        o[3] = d * o[3];
        o[4] = d * ((t1 * m[4] + t2 * m[8] + t5 * m[12]) - (t0 * m[4] + t3 * m[8] + t4 * m[12]));
        o[5] = d * ((t0 * m[0] + t7 * m[8] + t8 * m[12]) - (t1 * m[0] + t6 * m[8] + t9 * m[12]));
        o[6] = d * ((t3 * m[0] + t6 * m[4] + t11 * m[12]) - (t2 * m[0] + t7 * m[4] + t10 * m[12]));
        o[7] = d * ((t4 * m[0] + t9 * m[4] + t10 * m[8]) - (t5 * m[0] + t8 * m[4] + t11 * m[8]));
        o[8] = d * ((t12 * m[7] + t15 * m[11] + t16 * m[15]) - (t13 * m[7] + t14 * m[11] + t17 * m[15]));
        o[9] = d * ((t13 * m[3] + t18 * m[11] + t21 * m[15]) - (t12 * m[3] + t19 * m[11] + t20 * m[15]));
        o[10] = d * ((t14 * m[3] + t19 * m[7] + t22 * m[15]) - (t15 * m[3] + t18 * m[7] + t23 * m[15]));
        o[11] = d * ((t17 * m[3] + t20 * m[7] + t23 * m[11]) - (t16 * m[3] + t21 * m[7] + t22 * m[11]));
        o[12] = d * ((t14 * m[10] + t17 * m[14] + t13 * m[6]) - (t16 * m[14] + t12 * m[6] + t15 * m[10]));
        o[13] = d * ((t20 * m[14] + t12 * m[2] + t19 * m[10]) - (t18 * m[10] + t21 * m[14] + t13 * m[2]));
        o[14] = d * ((t18 * m[6] + t23 * m[14] + t15 * m[2]) - (t22 * m[14] + t14 * m[2] + t19 * m[6]));
        o[15] = d * ((t22 * m[10] + t16 * m[2] + t21 * m[6]) - (t20 * m[6] + t23 * m[10] + t17 * m[2]));

        return pMatrix;
    }

    std::unique_ptr<Matrix> Matrix::Transpose(const Matrix *otherMatrix)
    {
        std::unique_ptr<Matrix> pMatrix = std::make_unique<Matrix>();

        pMatrix->data[0] = otherMatrix->data[0];
        pMatrix->data[1] = otherMatrix->data[4];
        pMatrix->data[2] = otherMatrix->data[8];
        pMatrix->data[3] = otherMatrix->data[12];
        pMatrix->data[4] = otherMatrix->data[1];
        pMatrix->data[5] = otherMatrix->data[5];
        pMatrix->data[6] = otherMatrix->data[9];
        pMatrix->data[7] = otherMatrix->data[13];
        pMatrix->data[8] = otherMatrix->data[2];
        pMatrix->data[9] = otherMatrix->data[6];
        pMatrix->data[10] = otherMatrix->data[10];
        pMatrix->data[11] = otherMatrix->data[14];
        pMatrix->data[12] = otherMatrix->data[3];
        pMatrix->data[13] = otherMatrix->data[7];
        pMatrix->data[14] = otherMatrix->data[11];
        pMatrix->data[15] = otherMatrix->data[15];

        return pMatrix;
    }

    std::unique_ptr<Matrix> Matrix::Translation(const Vector3 *position)
    {
        std::unique_ptr<Matrix> pMatrix = Matrix::Identity();

        pMatrix->data[12] = position->x;
        pMatrix->data[13] = position->y;
        pMatrix->data[14] = position->z;

        return pMatrix;
    }

    std::unique_ptr<Matrix> Matrix::Scale(const Vector3 *scale)
    {
        std::unique_ptr<Matrix> pMatrix = Matrix::Identity();

        pMatrix->data[0] = scale->x;
        pMatrix->data[5] = scale->y;
        pMatrix->data[10] = scale->z;

        return pMatrix;
    }

    std::unique_ptr<Matrix> Matrix::EulerX(float angleRadians)
    {
        std::unique_ptr<Matrix> pMatrix = Matrix::Identity();
        float c = std::cos(angleRadians);
        float s = std::sin(angleRadians);

        pMatrix->data[5] = c;
        pMatrix->data[6] = s;
        pMatrix->data[9] = -s;
        pMatrix->data[10] = c;

        return pMatrix;
    }

    std::unique_ptr<Matrix> Matrix::EulerY(float angleRadians)
    {
        std::unique_ptr<Matrix> pMatrix = Matrix::Identity();
        float c = std::cos(angleRadians);
        float s = std::sin(angleRadians);

        pMatrix->data[5] = c;
        pMatrix->data[6] = -s;
        pMatrix->data[9] = s;
        pMatrix->data[10] = c;

        return pMatrix;
    }

    std::unique_ptr<Matrix> Matrix::EulerZ(float angleRadians)
    {
        std::unique_ptr<Matrix> pMatrix = Matrix::Identity();
        float c = std::cos(angleRadians);
        float s = std::sin(angleRadians);

        pMatrix->data[5] = c;
        pMatrix->data[6] = s;
        pMatrix->data[9] = -s;
        pMatrix->data[10] = c;

        return pMatrix;
    }

    std::unique_ptr<Matrix> Matrix::EulerXYZ(float xRadians, float yRadians, float zRadians)
    {
        std::unique_ptr<Matrix> rx = Matrix::EulerX(xRadians);
        std::unique_ptr<Matrix> ry = Matrix::EulerY(yRadians);
        std::unique_ptr<Matrix> rz = Matrix::EulerZ(zRadians);

        std::unique_ptr<Matrix> pMatrix = rx->Multiply(ry.get());
        pMatrix = pMatrix->Multiply(rz.get());

        return pMatrix;
    }

}