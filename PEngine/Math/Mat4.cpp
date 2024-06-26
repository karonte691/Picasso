/*
    Based on work by Copyright (C) 2012 Alexander Overvoorde

    Permission is hereby granted, free of charge, to any person obtaining a copy of
    this software and associated documentation files (the "Software"), to deal in
    the Software without restriction, including without limitation the rights to
    use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
    the Software, and to permit persons to whom the Software is furnished to do so,
    subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
    FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
    COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
    IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
    CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
*/
#include <PEngine/Math/Mat4.h>
#include <cmath>

namespace Picasso::Engine::Math
{
    Mat4::Mat4()
    {
        *this = Mat4(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1);
    }

    Mat4::Mat4(float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23, float v30, float v31, float v32, float v33)
    {
        m[0] = v00;
        m[4] = v01;
        m[8] = v02;
        m[12] = v03;
        m[1] = v10;
        m[5] = v11;
        m[9] = v12;
        m[13] = v13;
        m[2] = v20;
        m[6] = v21;
        m[10] = v22;
        m[14] = v23;
        m[3] = v30;
        m[7] = v31;
        m[11] = v32;
        m[15] = v33;
    }

    const Mat4 Mat4::operator*(const Mat4 &mat) const
    {
        return Mat4(
            m[0] * mat.m[0] + m[4] * mat.m[1] + m[8] * mat.m[2] + m[12] * mat.m[3], m[0] * mat.m[4] + m[4] * mat.m[5] + m[8] * mat.m[6] + m[12] * mat.m[7], m[0] * mat.m[8] + m[4] * mat.m[9] + m[8] * mat.m[10] + m[12] * mat.m[11], m[0] * mat.m[12] + m[4] * mat.m[13] + m[8] * mat.m[14] + m[12] * mat.m[15],
            m[1] * mat.m[0] + m[5] * mat.m[1] + m[9] * mat.m[2] + m[13] * mat.m[3], m[1] * mat.m[4] + m[5] * mat.m[5] + m[9] * mat.m[6] + m[13] * mat.m[7], m[1] * mat.m[8] + m[5] * mat.m[9] + m[9] * mat.m[10] + m[13] * mat.m[11], m[1] * mat.m[12] + m[5] * mat.m[13] + m[9] * mat.m[14] + m[13] * mat.m[15],
            m[2] * mat.m[0] + m[6] * mat.m[1] + m[10] * mat.m[2] + m[14] * mat.m[3], m[2] * mat.m[4] + m[6] * mat.m[5] + m[10] * mat.m[6] + m[14] * mat.m[7], m[2] * mat.m[8] + m[6] * mat.m[9] + m[10] * mat.m[10] + m[14] * mat.m[11], m[2] * mat.m[12] + m[6] * mat.m[13] + m[10] * mat.m[14] + m[14] * mat.m[15],
            m[3] * mat.m[0] + m[7] * mat.m[1] + m[11] * mat.m[2] + m[15] * mat.m[3], m[3] * mat.m[4] + m[7] * mat.m[5] + m[11] * mat.m[6] + m[15] * mat.m[7], m[3] * mat.m[8] + m[7] * mat.m[9] + m[11] * mat.m[10] + m[15] * mat.m[11], m[3] * mat.m[12] + m[7] * mat.m[13] + m[11] * mat.m[14] + m[15] * mat.m[15]);
    }

    const Vector3 Mat4::operator*(const Vector3 &v) const
    {
        return Vector3(
            m[0] * v.x + m[4] * v.y + m[8] * v.z + m[12],
            m[1] * v.x + m[5] * v.y + m[9] * v.z + m[13],
            m[2] * v.x + m[6] * v.y + m[10] * v.z + m[14]);
    }

    const Vector4 Mat4::operator*(const Vector4 &v) const
    {
        return Vector4(
            m[0] * v.x + m[4] * v.y + m[8] * v.z + m[12] * v.w,
            m[1] * v.x + m[5] * v.y + m[9] * v.z + m[13] * v.w,
            m[2] * v.x + m[6] * v.y + m[10] * v.z + m[14] * v.w,
            m[3] * v.x + m[7] * v.y + m[11] * v.z + m[15] * v.w);
    }

    void Mat4::Translate(const Vector3 &v)
    {
        *this = *this * Mat4(
                            1, 0, 0, v.x,
                            0, 1, 0, v.y,
                            0, 0, 1, v.z,
                            0, 0, 0, 1);
    }

    void Mat4::Scale(const Vector3 &v)
    {
        *this = *this * Mat4(
                            v.x, 0, 0, 0,
                            0, v.y, 0, 0,
                            0, 0, v.z, 0,
                            0, 0, 0, 1);
    }

    void Mat4::Rotate(const Mat4Rotation axisRotation, const float ang)
    {
        switch (axisRotation)
        {
        case Mat4Rotation::X:
            return _rotateOnX(ang);
            break;
        case Mat4Rotation::Y:
            return _rotateOnY(ang);
            break;
        case Mat4Rotation::Z:
            return _rotateOnZ(ang);
            break;
        default:
            break;
        }
    }

    void Mat4::LookAt(Vector3 eye, const Vector3 center, const Vector3 up)
    {
        eye.Sub(&center).Normalize();

        Vector3 X(
            up.y * eye.z - up.z * eye.y,
            up.z * eye.x - up.x * eye.z,
            up.x * eye.y - up.y * eye.x);

        Vector3 Y(
            eye.y * X.z - eye.z * X.y,
            eye.z * X.x - eye.x * X.z,
            eye.x * X.y - eye.y * X.x);

        X.Normalize();
        Y.Normalize();

        this->m[0] = X.x;
        this->m[1] = Y.x;
        this->m[2] = eye.x;
        this->m[4] = X.y;
        this->m[5] = Y.y;
        this->m[6] = eye.y;
        this->m[8] = X.z;
        this->m[9] = Y.z;
        this->m[10] = eye.z;
        this->m[12] = -X.Dot(&eye);
        this->m[13] = -Y.Dot(&eye);
        this->m[14] = -eye.Dot(&eye);
    }

    void Mat4::Perspective(float fovy, float aspect, float near, float far)
    {
        float top = near * std::tan(fovy / 2.0f);
        float right = top * aspect;
        float left = -right;
        float bottom = -top;

        this->m[0] = near * 2.0f / (right - left);
        this->m[5] = near * 2.0f / (top - bottom);
        this->m[8] = (right + left) / (right - left);
        this->m[9] = (top + bottom) / (top - bottom);
        this->m[10] = (-far - near) / (far - near);
        this->m[11] = -1;
        this->m[14] = -2.0f * far * near / (far - near);
        this->m[15] = 0;
    }

    void Mat4::_rotateOnY(const float ang)
    {
        *this = *this * Mat4(
                            1, 0, 0, 0,
                            0, std::cos(ang), -std::sin(ang), 0,
                            0, std::sin(ang), std::cos(ang), 0,
                            0, 0, 0, 1);
    }

    void Mat4::_rotateOnX(const float ang)
    {
        *this = *this * Mat4(
                            std::cos(ang), 0, std::sin(ang), 0,
                            0, 1, 0, 0,
                            -std::sin(ang), 0, std::cos(ang), 0,
                            0, 0, 0, 1);
    }

    void Mat4::_rotateOnZ(const float ang)
    {
        *this = *this * Mat4(
                            std::cos(ang), -std::sin(ang), 0, 0,
                            std::sin(ang), std::cos(ang), 0, 0,
                            0, 0, 1, 0,
                            0, 0, 0, 1);
    }

    std::unique_ptr<Mat4> Mat4::Identity()
    {
        return std::make_unique<Mat4>(1.0f, 0.0f, 0.0f, 0.0f,
                                      0.0f, 1.0f, 0.0f, 0.0f,
                                      0.0f, 0.0f, 1.0f, 0.0f,
                                      0.0f, 0.0f, 0.0f, 1.0f);
    }
}