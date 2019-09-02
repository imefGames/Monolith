#pragma once

namespace Monolith
{
    namespace Math
    {
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
    }
}