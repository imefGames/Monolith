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

    void RenderingContext::CleanBuffer()
    {
        for (s8& pixel : m_CanvasBuffer)
        {
            pixel = ' ';
        }
    }

    void RenderingContext::DrawPoint(const Vec2& pixelPosition)
    {
        DrawCharacter(pixelPosition, '*');
    }

    void RenderingContext::DrawCharacter(const Vec2& pixelPosition, s8 character)
    {
        u32 pixelX{ static_cast<u32>(pixelPosition.GetX()) };
        u32 pixelY{ static_cast<u32>(pixelPosition.GetY()) };

        if (pixelX < m_CanvasWidth && pixelY < m_CanvasHeight)
        {
            m_CanvasBuffer[pixelX + pixelY * static_cast<u64>(m_CanvasWidth)] = character;
        }
    }

    void RenderingContext::DrawText(const Vec2& textPosition, const std::string& text)
    {
        u32 pixelX{ static_cast<u32>(textPosition.GetX()) };
        u32 pixelY{ static_cast<u32>(textPosition.GetY()) };

        if (pixelY < m_CanvasHeight)
        {
            for (u64 i = 0; i < text.size() && pixelX + i < m_CanvasWidth; ++i)
            {
                m_CanvasBuffer[pixelX + i + pixelY * static_cast<u64>(m_CanvasWidth)] = text[i];
            }
        }
    }

    void RenderingContext::DrawRectangle(const Vec2& topLeftPosition, const Vec2& bottomRightPosition)
    {
        u32 topLeftX{ static_cast<u32>(topLeftPosition.GetX()) };
        u32 topLeftY{ static_cast<u32>(topLeftPosition.GetY()) };
        u32 bottomRightX{ Math::Min(static_cast<u32>(bottomRightPosition.GetX()), m_CanvasWidth) };
        u32 bottomRightY{ Math::Min(static_cast<u32>(bottomRightPosition.GetY()), m_CanvasHeight) };

        for (u32 j = topLeftY; j < bottomRightY; ++j)
        {
            for (u32 i = topLeftX; i < bottomRightX; ++i)
            {
                s8 character = ' ';
                bool isBorderHor{ i == topLeftX || i == bottomRightX - 1 };
                bool isBorderVer{ j == topLeftY || j == bottomRightY - 1 };
                if (isBorderHor && isBorderVer)
                {
                    character = '+';
                }
                else if (isBorderHor)
                {
                    character = '|';
                }
                else if (isBorderVer)
                {
                    character = '-';
                }
                m_CanvasBuffer[i + j * static_cast<u64>(m_CanvasWidth)] = character;
            }
        }
    }
}