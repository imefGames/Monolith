#include <precomp.h>
#include <core/matrixmath.h>

namespace Monolith
{
    namespace Math
    {
        namespace Matrix
        {
            Mat44f PerspectiveProjection(f32 fieldOfView, f32 aspectRatio, f32 screenNear, f32 screenDepth)
            {
                f32 scale{ 1 / std::tan(fieldOfView * 0.5f) };

                Mat44f result;
                result(0, 0) = scale / aspectRatio;
                result(1, 1) = scale;
                result(2, 2) = screenDepth / (screenDepth - screenNear);
                result(2, 3) = -screenDepth * screenNear / (screenDepth - screenNear);
                result(3, 2) = 1.0f;
                return result;
            }

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

            Mat44f Transpose(const Mat44f& mat44)
            {
                Mat44f result;
                for (u32 j = 0; j < 4; ++j)
                {
                    for (u32 i = 0; i < 4; ++i)
                    {
                        result(i, j) = mat44(j, i);
                    }
                }
                return result;
            }

            Mat44f Multiply(const Mat44f& lhs, const Mat44f& rhs)
            {
                Mat44f result;
                for (u32 j = 0; j < 4; ++j)
                {
                    for (u32 i = 0; i < 4; ++i)
                    {
                        f32 value{ 0.0f };
                        for (u32 k = 0; k < 4; ++k)
                        {
                            value += lhs(i, k) * rhs(k, j);
                        }
                        result(i, j) = value;
                    }
                }
                return result;
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