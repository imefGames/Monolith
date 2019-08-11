#include <precomp.h>
#include <engine/rendering/gamerenderer.h>

#include <engine/rendering/renderingcontext.h>

#include <Windows.h>

namespace Monolith
{
    void GameRenderer::OnInit()
    {
        RegisterInstance(this);
    }

    void GameRenderer::OnShutdown()
    {
        UnregisterInstance(this);
    }

    void GameRenderer::StartFrame(RenderingContext& renderingContext)
    {
        u32 bufferSize{ renderingContext.m_CanvasWidth * renderingContext.m_CanvasHeight };
        if (bufferSize > renderingContext.m_CanvasBuffer.size())
        {
            renderingContext.m_CanvasBuffer.resize(bufferSize);
        }

        renderingContext.CleanBuffer();
    }

    void GameRenderer::EndFrame(RenderingContext& renderingContext)
    {
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(out, &cursorInfo);

        COORD pos = { 0, 0 };
        HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(output, pos);

        for (u32 j = 0; j < renderingContext.m_CanvasHeight; ++j)
        {
            for (u32 i = 0; i < renderingContext.m_CanvasWidth; ++i)
            {
                putc(renderingContext.m_CanvasBuffer[i + j * static_cast<u64>(renderingContext.m_CanvasWidth)], stdout);
            }
            putc('\n', stdout);
        }
    }

    namespace RenderingHelper
    {
        void StartFrame(RenderingContext& renderingContext)
        {
            GameRenderer* gameRenderer{ GameRenderer::Get() };
            if (gameRenderer != nullptr)
            {
                gameRenderer->StartFrame(renderingContext);
            }
        }

        void EndFrame(RenderingContext& renderingContext)
        {
            GameRenderer* gameRenderer{ GameRenderer::Get() };
            if (gameRenderer != nullptr)
            {
                gameRenderer->EndFrame(renderingContext);
            }
        }
    }
}