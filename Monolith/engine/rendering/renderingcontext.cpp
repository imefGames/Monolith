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

    void RenderingContext::DrawPoint(const Vec2f& pixelPosition)
    {
    }

    void RenderingContext::DrawCharacter(const Vec2f& pixelPosition, s8 character)
    {
    }

    void RenderingContext::DrawText(const Vec2f& textPosition, const std::string& text)
    {
    }

    void RenderingContext::DrawRectangle(const Vec2f& topLeftPosition, const Vec2f& bottomRightPosition)
    {
    }
}