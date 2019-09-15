#include <precomp.h>
#include <engine/rendering/renderingcontext.h>

namespace Monolith
{
    RenderingContext::RenderingContext()
        : m_CanvasWidth{ 1 }
        , m_CanvasHeight{ 1 }
    {
    }

    void RenderingContext::SetWindowSize(u32 windowWidth, u32 windowHeight)
    {
        m_CanvasWidth = windowWidth;
        m_CanvasHeight = windowHeight;
    }

    void RenderingContext::DrawPoint(const Vec2& pixelPosition)
    {
    }

    void RenderingContext::DrawCharacter(const Vec2& pixelPosition, s8 character)
    {
    }

    void RenderingContext::DrawText(const Vec2& textPosition, const std::string& text)
    {
    }

    void RenderingContext::DrawRectangle(const Vec2& topLeftPosition, const Vec2& bottomRightPosition)
    {
    }
}