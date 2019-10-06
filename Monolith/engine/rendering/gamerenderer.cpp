#include <precomp.h>
#include <engine/rendering/gamerenderer.h>

#include <engine/rendering/graphicswrapper.h>
#include <engine/rendering/renderingcontext.h>
#include <engine/window/gamewindowdata.h>


#include <engine/rendering/model.h>
#include <engine/rendering/shaders/shader.h>

#include <Windows.h>

namespace Monolith
{
    const bool K_FULL_SCREEN = false;
    const bool K_VSYNC_ENABLED = true;
    const f32 K_SCREEN_DEPTH = 1000.0f;
    const f32 K_SCREEN_NEAR = 0.1f;
    const f32 K_FIELD_OF_VIEW = Math::PI / 4.0f;

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
        m_GraphicsWrapper = new GraphicsWrapper{};
        m_GraphicsWrapper->Init(gameWindowData.GetScreenWidth(), gameWindowData.GetScreenHeight(), K_VSYNC_ENABLED, gameWindowData.GetWindowHandle(), K_FULL_SCREEN);

        m_GraphicDeviceData.SetupDevice(*m_GraphicsWrapper);
    }

    void GameRenderer::ShutdownGraphics()
    {
        m_GraphicsWrapper->Shutdown();
        delete m_GraphicsWrapper;
        m_GraphicsWrapper = nullptr;
    }

    void GameRenderer::StartFrame(RenderingContext& renderingContext)
    {
        renderingContext.m_Camera.SetFromPosition(Vec4f{ 0.0f, 0.0f, -10.0f });
        renderingContext.m_GraphicsWrapper = m_GraphicsWrapper;
        renderingContext.m_Camera.ComputeViewMatrix();
        renderingContext.m_ViewMatrix = renderingContext.m_Camera.GetViewMatrix();
        renderingContext.m_WorldMatrix = Mat44f::GetIdentity();
        //TODO: get aspect ratio from screen size.
        renderingContext.m_ProjectionMatrix = Math::Matrix::PerspectiveProjection(K_FIELD_OF_VIEW, 800.0f/600.0f, K_SCREEN_NEAR, K_SCREEN_DEPTH);

        m_GraphicsWrapper->BeginFrame();

        Shader s;
        Model m;

        s.Init();
        m.Init();

        m.SetupRender(renderingContext);
        s.Render(renderingContext, m.GetIndexCount());

        m.Shutdown();
        s.Shutdown();
    }

    void GameRenderer::EndFrame(RenderingContext& renderingContext)
    {
        m_GraphicsWrapper->EndFrame();
        renderingContext.m_GraphicsWrapper = nullptr;
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