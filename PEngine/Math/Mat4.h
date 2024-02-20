#pragma once

#ifndef MAT_4_H
#define MAT_4_H

#include <PEngine/Math/Vector3.h>
#include <PEngine/Math/Vector4.h>

// taken from https://github.com/Overv/OOGL/blob/master/include/GL/Math/Mat4.hpp. All credits to them
namespace Picasso::Engine::Math
{
    enum class Mat4Rotation
    {
        X,
        Y,
        Z
    };

    class Mat4
    {
    public:
        float m[16];

        Mat4();
        Mat4(
            float v00, float v01, float v02, float v03,
            float v10, float v11, float v12, float v13,
            float v20, float v21, float v22, float v23,
            float v30, float v31, float v32, float v33);

        const Mat4 operator*(const Mat4 &mat) const;
        const Vector3 operator*(const Vector3 &v) const;
        const Vector4 operator*(const Vector4 &v) const;

        void Translate(const Vector3 &v);
        void Scale(const Vector3 &v);
        void Rotate(const Mat4Rotation axisRotation, const float ang);

        static std::unique_ptr<Mat4> Identity();

    private:
        void _rotateOnX(const float ang);
        void _rotateOnY(const float ang);
        void _rotateOnZ(const float ang);
    };
}
#endif