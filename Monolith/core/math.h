#pragma once

namespace Monolith
{
    namespace Math
    {
        constexpr float PI = 3.1415926536f;

        template <class T>
        T Min(T rhs, T lhs)
        {
            return (rhs > lhs ? lhs : rhs);
        }

        template <class T>
        T Max(T rhs, T lhs)
        {
            return (rhs > lhs ? rhs : lhs);
        }

        f32 Sqrt(f32 x);
    }
}