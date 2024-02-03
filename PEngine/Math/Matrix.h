#pragma once

#ifndef MATRIX_H
#define MATRIX_H

#include <memory>
#include <bits/floatn-common.h>
#include <PEngine/Math/Vector3.h>

namespace Picasso::Engine::Math
{
    class Matrix
    {
    public:
        _Float32 data[16];

        std::unique_ptr<Matrix> Multiply(const Matrix *otherMatrix);

        static std::unique_ptr<Matrix> Identity();

        /**
         * Creates and returns an orthographic projection matrix. Typically used to
         * render flat or 2D scenes.
         **/
        static std::unique_ptr<Matrix> Ortographic(_Float32 left,
                                                   _Float32 right,
                                                   _Float32 top,
                                                   _Float32 bottom,
                                                   _Float32 nearClip,
                                                   _Float32 farClip);

        /**
         * Creates and returns a perspective matrix. Typically used to render 3d scenes.
         **/
        static std::unique_ptr<Matrix> Perspective(_Float32 fovRadians, _Float32 aspectRation, _Float32 nearClip, _Float32 farClip);

        /**
         * Creates and returns a look-at matrix, or a matrix looking
         * at target from the perspective of position.
         **/
        static std::unique_ptr<Matrix> LookAt(const Vector3 *position, const Vector3 *target, const Vector3 *up);

        /**
         * Creates and returns an inverse of the provided matrix.
         **/
        static std::unique_ptr<Matrix> Inverse(const Matrix *otherMatrix);
        static std::unique_ptr<Matrix> Translation(const Vector3 *position);
        static std::unique_ptr<Matrix> Scale(const Vector3 *scale);
    };
}

#endif