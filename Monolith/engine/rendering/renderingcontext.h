#pragma once

#include <engine/rendering/camera.h>

#include <vector>
#include <string>

namespace Monolith
{
    class RenderingContext
    {
        friend class GameRenderer;
        friend class GameWindow;

    public:
        RenderingContext();

        void DrawPoint(const Vec2f& pixelPosition);
        void DrawCharacter(const Vec2f& pixelPosition, s8 character);
        void DrawText(const Vec2f& textPosition, const std::string& text);
        void DrawRectangle(const Vec2f& topLeftPosition, const Vec2f& bottomRightPosition);

    private:
        void SetWindowSize(u32 windowWidth, u32 windowHeight);

        Camera m_Camera;
    };
}