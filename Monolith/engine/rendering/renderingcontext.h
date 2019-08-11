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

        void DrawPoint(u32 pixelX, u32 pixelY);

    private:
        void SetWindowSize(u32 windowWidth, u32 windowHeight);
        void CleanBuffer();

        std::vector<s8> m_CanvasBuffer;
        u32 m_CanvasWidth;
        u32 m_CanvasHeight;
    };
}