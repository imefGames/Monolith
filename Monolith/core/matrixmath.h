#pragma once

#include <core/vectorgeneric.hpp>
#include <core/matrixgeneric.hpp>

namespace Monolith
{
    namespace Math
    {
        namespace Matrix
        {
            Mat44f PerspectiveProjection(f32 fieldOfView, f32 aspectRatio, f32 screenNear, f32 screenDepth);
            Mat44f OrthographicProjection(f32 left, f32 top, f32 right, f32 bottom, f32 screenNear, f32 screenDepth);
            Mat44f OrthographicProjection(f32 width, f32 height, f32 screenNear, f32 screenDepth);
            Mat33f SubMatrix(const Mat44f& mat44, u32 ignoredColumn, u32 ignoredRow);
            Mat44f Transpose(const Mat44f& mat44);
            Mat44f Multiply(const Mat44f& lhs, const Mat44f& rhs);

            f32 Determinant(const Mat22f& mat22);
            f32 Determinant(const Mat33f& mat33);
            f32 Determinant(const Mat44f& mat44);
        }
    }
}