#include <precomp.h>
#include <core/vector2.h>

namespace Monolith
{
    Vec2::Vec2(u32 x, u32 y)
        : m_X{ x }
        , m_Y{ y }
    {
    }

    Vec2 operator+(const Vec2& rhs, const Vec2& lhs)
    {
        Vec2 newVector;
        newVector.GetX() = rhs.GetX() + lhs.GetX();
        newVector.GetY() = rhs.GetY() + lhs.GetY();
        return newVector;
    }
}