#pragma once

namespace Monolith
{
    class Vec2
    {
    public:
        Vec2() = default;
        Vec2(f32 x, f32 y);

        f32 GetX() const { return m_X; };
        f32 GetY() const { return m_Y; };

        f32& GetX() { return m_X; };
        f32& GetY() { return m_Y; };

    private:
        f32 m_X = 0;
        f32 m_Y = 0;

        friend Vec2 operator+(const Vec2& rhs, const Vec2& lhs);
    };

    Vec2 operator+(const Vec2& rhs, const Vec2& lhs);
}