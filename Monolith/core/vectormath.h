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

            template <class DataType, u32 VectorSize>
            VecGeneric<DataType, VectorSize> Normalize(const VecGeneric<DataType, VectorSize>& vector)
            {
                VecGeneric<DataType, VectorSize> newVector{ vector };
                DataType distance{ Math::Sqrt(DotProduct(newVector, newVector)) };
                for (u32 i = 0; i < VectorSize; ++i)
                {
                    newVector[i] /= distance;
                }
                return newVector;
            }

            Vec3f CrossProduct(const Vec3f& vector1, const Vec3f& vector2);
        }
    }
}