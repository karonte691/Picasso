#include <PEngine/Math/Matrix.h>

namespace Picasso::Engine::Math
{
    std::unique_ptr<Matrix> Matrix::Multiply(const Matrix *otherMatrix)
    {
        std::unique_ptr<Matrix> pMatrix = Matrix::Identity();

        const _Float32 *thisData = this->data;
        const _Float32 *otherData = otherMatrix->data;
        _Float32 *dst = pMatrix->data;

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

    std::unique_ptr<Matrix> Matrix::Ortographic()
    {
        std::unique_ptr<Matrix> pMatrix = Matrix::Identity();

        return pMatrix;
    }
}