#pragma once

#ifndef MATRIX_H
#define MATRIX_H

#include <memory>
#include <bits/floatn-common.h>

namespace Picasso::Engine::Math
{
    class Matrix
    {
    public:
        _Float32 data[16];

        std::unique_ptr<Matrix> Multiply(const Matrix *otherMatrix);

        static std::unique_ptr<Matrix> Identity();
        static std::unique_ptr<Matrix> Ortographic();
    };
}

#endif