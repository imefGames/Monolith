#pragma once

#include <core/types.h>

namespace Monolith
{
    template <class DataType, u32 VectorSize>
    class MatrixGeneric
    {
    public:
        static constexpr u32 K_MAX_ELEMENTS{ VectorSize * VectorSize };

        MatrixGeneric()
        {
            for (DataType& currentValue : m_Values)
            {
                currentValue = 0.0f;
            }
        }

        template <class OtherDataType, u32 OtherVectorSize>
        MatrixGeneric(const MatrixGeneric<OtherDataType, OtherVectorSize>& otherVector)
            : MatrixGeneric{}
        {
            u32 maxIndex{ Math::Min(K_MAX_ELEMENTS, MatrixGeneric<OtherDataType, OtherVectorSize>::K_MAX_ELEMENTS) };
            for (u32 i = 0; i < maxIndex; ++i)
            {
                m_Values[i] = otherVector.m_Values[i];
            }
        }

        template <class ... Args>
        MatrixGeneric(const Args&... values)
            : m_Values{ values... }
        {
        }

        inline DataType& operator[](u32 index) { return m_Values[index]; }
        inline const DataType& operator[](u32 index) const { return m_Values[index]; }

        inline DataType& operator()(u32 indexX, u32 indexY) { return m_Values[indexY * VectorSize + indexX]; }
        inline const DataType& operator()(u32 indexX, u32 indexY) const { return m_Values[indexY * VectorSize + indexX]; }

        static MatrixGeneric<DataType, VectorSize> GetIdentity()
        {
            MatrixGeneric<DataType, VectorSize> newMatrix{};
            for (u32 i = 0; i < VectorSize; ++i)
            {
                newMatrix.m_Values[(1 + VectorSize) * i] = 1;
            }
            return newMatrix;
        }

    private:
        DataType m_Values[K_MAX_ELEMENTS];
    };

    template <class DataType, u32 VectorSize>
    MatrixGeneric<DataType, VectorSize> operator+(const MatrixGeneric<DataType, VectorSize>& rhs, const MatrixGeneric<DataType, VectorSize>& lhs)
    {
        MatrixGeneric<DataType, VectorSize> newVector{ rhs };
        for (u32 i = 0; i < MatrixGeneric<DataType, VectorSize>::K_MAX_ELEMENTS; ++i)
        {
            newVector[i] += lhs[i];
        }
        return newVector;
    }

    using Mat22f = MatrixGeneric<f32, 2>;
    using Mat33f = MatrixGeneric<f32, 3>;
    using Mat44f = MatrixGeneric<f32, 4>;
}