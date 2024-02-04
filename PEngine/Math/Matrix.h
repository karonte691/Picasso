#pragma once

#ifndef MATRIX_H
#define MATRIX_H

#include <memory>

#include <PEngine/Math/Vector3.h>

namespace Picasso::Engine::Math
{
    class Matrix
    {
    public:
        float data[16];

        std::unique_ptr<Matrix> Multiply(const Matrix *otherMatrix);

        static std::unique_ptr<Matrix> Identity();

        /**
         * Creates and returns an orthographic projection matrix. Typically used to
         * render flat or 2D scenes.
         **/
        static std::unique_ptr<Matrix> Ortographic(float left,
                                                   float right,
                                                   float top,
                                                   float bottom,
                                                   float nearClip,
                                                   float farClip);

        /**
         * Creates and returns a perspective matrix. Typically used to render 3d scenes.
         **/
        static std::unique_ptr<Matrix> Perspective(float fovRadians, float aspectRation, float nearClip, float farClip);

        /**
         * Creates and returns a look-at matrix, or a matrix looking
         * at target from the perspective of position.
         **/
        static std::unique_ptr<Matrix> LookAt(const Vector3 *position, const Vector3 *target, const Vector3 *up);

        /**
         * Creates and returns an inverse of the provided matrix.
         **/
        static std::unique_ptr<Matrix> Inverse(const Matrix *otherMatrix);

        /**
         * Returns a transposed copy of the provided matrix (rows->colums)
         **/
        static std::unique_ptr<Matrix> Transpose(const Matrix *otherMatrix);
        static std::unique_ptr<Matrix> Translation(const Vector3 *position);
        static std::unique_ptr<Matrix> Scale(const Vector3 *scale);
        static std::unique_ptr<Matrix> EulerX(float angleadians);
        static std::unique_ptr<Matrix> EulerY(float angleadians);
        static std::unique_ptr<Matrix> EulerZ(float angleadians);
        static std::unique_ptr<Matrix> EulerXYZ(float xRadians, float yRadians, float zRadians);
    };
}

#endif