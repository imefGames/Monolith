#include <precomp.h>
#include <core/matrixmath.h>

namespace Monolith
{
    namespace Math
    {
        namespace Matrix
        {
            Mat33f SubMatrix(const Mat44f& mat44, u32 ignoredColumn, u32 ignoredRow)
            {
                Mat33f newMatrix{};
                u32 newJ{ 0 };
                for (u32 j = 0; j < 4; ++j)
                {
                    if (j != ignoredRow)
                    {
                        u32 newI{ 0 };
                        for (u32 i = 0; i < 4; ++i)
                        {
                            if (i != ignoredColumn)
                            {
                                newMatrix(newI, newJ) = mat44(i, j);
                                ++newI;
                            }
                        }
                        ++newJ;
                    }
                }
                return newMatrix;
            }

            f32 Determinant(const Mat22f& mat22)
            {
                return (mat22(0, 0) * mat22(1, 1) - mat22(1, 0) * mat22(0, 1));
            }

            f32 Determinant(const Mat33f& mat33)
            {
                return (mat33(0, 0) * mat33(1, 1) * mat33(2, 2) +
                        mat33(1, 0) * mat33(2, 1) * mat33(0, 2) +
                        mat33(2, 0) * mat33(0, 1) * mat33(1, 2) -
                        mat33(2, 0) * mat33(1, 1) * mat33(0, 2) -
                        mat33(1, 0) * mat33(0, 1) * mat33(2, 2) -
                        mat33(0, 0) * mat33(2, 1) * mat33(1, 2));
            }

            f32 Determinant(const Mat44f& mat44)
            {
                f32 det{ 0.0f };
                for (u32 i = 0; i < 4; ++i)
                {
                    Mat33f subMatrix{ SubMatrix(mat44, i, 0) };
                    f32 subDet{ mat44(i, 0) * Determinant(subMatrix) };
                    if (i % 2 == 0)
                    {
                        det += subDet;
                    }
                    else
                    {
                        det -= subDet;
                    }
                }
                return det;
            }
        }
    }
}