#pragma once

#include <core/vectorgeneric.hpp>

namespace Monolith
{
    namespace Math
    {
        namespace Vector
        {
            template <class DataType, u32 VectorSize>
            DataType DotProduct(const VecGeneric<DataType, VectorSize>& vector1, const VecGeneric<DataType, VectorSize>& vector2)
            {
                DataType result{ 0.0f };
                for (u32 i = 0; i < VectorSize; ++i)
                {
                    result += vector1[i] * vector2[i];
                }
                return result;
            }
        }
    }
}