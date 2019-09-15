#include <precomp.h>
#include <engine/rendering/gamerenderer.h>

#include <engine/rendering/graphicswrapper.h>
#include <engine/rendering/renderingcontext.h>
#include <engine/window/gamewindowdata.h>

#include <Windows.h>

namespace Monolith
{
    GameRenderer::GameRenderer()
        : m_GraphicsWrapper{ nullptr }
    {
    }

    void GameRenderer::OnInit()
    {
        RegisterInstance(this);
    }

    void GameRenderer::OnShutdown()
    {
        UnregisterInstance(this);
    }

    void GameRenderer::InitGraphics(const GameWindowData& gameWindowData)
    {
        const bool K_FULL_SCREEN = false;
        const bool K_VSYNC_ENABLED = true;
        const float K_SCREEN_DEPTH = 1000.0f;
        const float K_SCREEN_NEAR = 0.1f;
        m_GraphicsWrapper = new GraphicsWrapper{};
        m_GraphicsWrapper->Init(gameWindowData.GetScreenWidth(), gameWindowData.GetScreenHeight(), K_VSYNC_ENABLED, gameWindowData.GetWindowHandle(), K_FULL_SCREEN, K_SCREEN_DEPTH, K_SCREEN_NEAR);
    }

    void GameRenderer::ShutdownGraphics()
    {
        m_GraphicsWrapper->Shutdown();
        delete m_GraphicsWrapper;
        m_GraphicsWrapper = nullptr;
    }

    void GameRenderer::StartFrame(RenderingContext& renderingContext)
    {
        m_GraphicsWrapper->BeginFrame();
    }

    void GameRenderer::EndFrame(RenderingContext& renderingContext)
    {
        m_GraphicsWrapper->EndFrame();
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

        void InitGraphics(const GameWindowData& gameWindowData)
        {
            GameRenderer* gameRenderer{ GameRenderer::Get() };
            if (gameRenderer != nullptr)
            {
                gameRenderer->InitGraphics(gameWindowData);
            }
        }

        void ShutdownGraphics()
        {
            GameRenderer* gameRenderer{ GameRenderer::Get() };
            if (gameRenderer != nullptr)
            {
                gameRenderer->ShutdownGraphics();
            }
        }
    }
}