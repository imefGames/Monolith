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

    void RenderingContext::DrawPoint(u32 pixelX, u32 pixelY)
    {
        if (pixelX < m_CanvasWidth && pixelY < m_CanvasHeight)
        {
            m_CanvasBuffer[pixelX + pixelY * static_cast<u64>(m_CanvasWidth)] = '*';
        }
    }
}