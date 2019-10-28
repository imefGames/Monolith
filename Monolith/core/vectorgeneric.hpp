#pragma once

#include <core/types.h>

namespace Monolith
{
    template <class DataType, u32 VectorSize>
    class VecGeneric
    {
    public:
        VecGeneric()
        {
            for (DataType& currentValue : m_Values)
            {
                currentValue = 0.0f;
            }
        }

        template <class OtherDataType, u32 OtherVectorSize>
        VecGeneric(const VecGeneric<OtherDataType, OtherVectorSize>& otherVector)
            : VecGeneric{}
        {
            u32 maxIndex{ Math::Min(VectorSize, OtherVectorSize) };
            for (u32 i = 0; i < maxIndex; ++i)
            {
                m_Values[i] = otherVector[i];
            }
        }

        template <class ... Args>
        VecGeneric(const Args&... values)
            : m_Values{ values... }
        {
        }

        inline DataType& operator[](u32 index) { return m_Values[index]; }
        inline const DataType& operator[](u32 index) const { return m_Values[index]; }

    private:
        DataType m_Values[VectorSize];
    };

    template <class DataType, u32 VectorSize>
    VecGeneric<DataType, VectorSize> operator+(const VecGeneric<DataType, VectorSize>& rhs, const VecGeneric<DataType, VectorSize>& lhs)
    {
        VecGeneric<DataType, VectorSize> newVector{ rhs };
        for (u32 i = 0; i < VectorSize; ++i)
        {
            newVector[i] += lhs[i];
        }
        return newVector;
    }

    template <class DataType, u32 VectorSize>
    VecGeneric<DataType, VectorSize> operator-(const VecGeneric<DataType, VectorSize>& rhs, const VecGeneric<DataType, VectorSize>& lhs)
    {
        VecGeneric<DataType, VectorSize> newVector{ rhs };
        for (u32 i = 0; i < VectorSize; ++i)
        {
            newVector[i] -= lhs[i];
        }
        return newVector;
    }

    template <class DataType, u32 VectorSize>
    VecGeneric<DataType, VectorSize> operator+(const VecGeneric<DataType, VectorSize>& rhs, DataType lhs)
    {
        VecGeneric<DataType, VectorSize> newVector{ rhs };
        for (u32 i = 0; i < VectorSize; ++i)
        {
            newVector[i] += lhs;
        }
        return newVector;
    }

    template <class DataType, u32 VectorSize>
    VecGeneric<DataType, VectorSize> operator-(const VecGeneric<DataType, VectorSize>& rhs, DataType lhs)
    {
        VecGeneric<DataType, VectorSize> newVector{ rhs };
        for (u32 i = 0; i < VectorSize; ++i)
        {
            newVector[i] -= lhs;
        }
        return newVector;
    }

    template <class DataType, u32 VectorSize>
    VecGeneric<DataType, VectorSize> operator*(const VecGeneric<DataType, VectorSize>& rhs, DataType lhs)
    {
        VecGeneric<DataType, VectorSize> newVector{ rhs };
        for (u32 i = 0; i < VectorSize; ++i)
        {
            newVector[i] *= lhs;
        }
        return newVector;
    }

    template <class DataType, u32 VectorSize>
    VecGeneric<DataType, VectorSize> operator/(const VecGeneric<DataType, VectorSize>& rhs, DataType lhs)
    {
        VecGeneric<DataType, VectorSize> newVector{ rhs };
        for (u32 i = 0; i < VectorSize; ++i)
        {
            newVector[i] /= lhs;
        }
        return newVector;
    }

    using Vec2f = VecGeneric<f32, 2>;
    using Vec3f = VecGeneric<f32, 3>;
    using Vec4f = VecGeneric<f32, 4>;
}