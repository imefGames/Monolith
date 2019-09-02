#pragma once

#include <vector>

namespace Monolith
{
    class RenderingContext
    {
        friend class GameRenderer;
        friend class GameWindow;

    public:
        RenderingContext();

        void DrawPoint(const Vec2& pixelPosition);
        void DrawCharacter(const Vec2& pixelPosition, s8 character);
        void DrawRectangle(const Vec2& topLeftPosition, const Vec2& bottomRightPosition);

    private:
        void SetWindowSize(u32 windowWidth, u32 windowHeight);
        void CleanBuffer();

        std::vector<s8> m_CanvasBuffer;
        u32 m_CanvasWidth;
        u32 m_CanvasHeight;
    };
}