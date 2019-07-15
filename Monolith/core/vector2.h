#pragma once

namespace Monolith
{
    class Vec2
    {
    public:
        Vec2() = default;
        Vec2(u32 x, u32 y);

        u32 GetX() const { return m_X; };
        u32 GetY() const { return m_Y; };

        u32& GetX() { return m_X; };
        u32& GetY() { return m_Y; };

    private:
        u32 m_X = 0;
        u32 m_Y = 0;

        friend Vec2 operator+(const Vec2& rhs, const Vec2& lhs);
    };

    Vec2 operator+(const Vec2& rhs, const Vec2& lhs);
}