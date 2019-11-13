#include <precomp.h>
#include <engine/rendering/gamerenderer.h>

#include <engine/rendering/font.h>
#include <engine/rendering/gamerendererinitdata.h>
#include <engine/rendering/graphicswrapper.h>
#include <engine/rendering/renderingcontext.h>
#include <engine/rendering/texture.h>
#include <engine/rendering/shaders/shader.h>
#include <engine/window/gamewindowdata.h>

#include <Windows.h>

namespace Monolith
{
    const bool K_FULL_SCREEN = false;
    const bool K_VSYNC_ENABLED = true;
    const f32 K_SCREEN_DEPTH = 1000.0f;
    const f32 K_SCREEN_NEAR = 0.1f;
    const f32 K_FIELD_OF_VIEW = Math::PI / 4.0f;

    GameRenderer::GameRenderer(const GameRendererInitData& initData)
        : m_GraphicsWrapper{ nullptr }
        , m_DefaultShader{ nullptr }
        , m_Texture{ nullptr }
        , m_DefaultFont{ nullptr }
        , m_DefaultShaderInitData{ initData.GetDefaultShader() }
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

        m_DefaultShader = new Shader{};
        m_DefaultShader->Init(m_DefaultShaderInitData);

        m_Texture = new Texture{};
        m_Texture->Initialize("minesweeper/textures/default.png");

        m_DefaultFont = new Font{};
        m_DefaultFont->Initialize("minesweeper/textures/defaultFont.png", "minesweeper/textures/defaultFontData.txt");
    }

    void GameRenderer::ShutdownGraphics()
    {
        m_DefaultShader->Shutdown();
        delete m_DefaultShader;
        m_DefaultShader = nullptr;

        m_GraphicsWrapper->Shutdown();
        delete m_GraphicsWrapper;
        m_GraphicsWrapper = nullptr;

        m_Texture->Shutdown();
        delete m_Texture;
        m_Texture = nullptr;

        m_DefaultFont->Shutdown();
        delete m_DefaultFont;
        m_DefaultFont = nullptr;
    }

    void GameRenderer::StartFrame(RenderingContext& renderingContext)
    {
        renderingContext.m_Camera.SetFromPosition(Vec4f{ 0.0f, 0.0f, -10.0f });
        renderingContext.m_GraphicsWrapper = m_GraphicsWrapper;
        renderingContext.m_Camera.ComputeViewMatrix();
        renderingContext.m_ViewMatrix = renderingContext.m_Camera.GetViewMatrix();
        renderingContext.m_WorldMatrix = Mat44f::GetIdentity();
        //TODO: get aspect ratio from screen size.
        renderingContext.m_ProjectionMatrix = Math::Matrix::OrthographicProjection(0.0f, 0.0f, 800.0f, 600.0f, K_SCREEN_NEAR, K_SCREEN_DEPTH);
        //renderingContext.m_ProjectionMatrix = Math::Matrix::PerspectiveProjection(K_FIELD_OF_VIEW, 800.0f/600.0f, K_SCREEN_NEAR, K_SCREEN_DEPTH);
        renderingContext.m_DefaultShader = m_DefaultShader;
        renderingContext.m_CurrentShader = renderingContext.m_DefaultShader;
        renderingContext.SetTexture(m_Texture);
        renderingContext.SetFont(m_DefaultFont);

        m_GraphicsWrapper->BeginFrame();

        m_GraphicsWrapper->SetZBufferActive(false);
        m_GraphicsWrapper->SetAlphaBlendingActive(true);
    }

    void GameRenderer::EndFrame(RenderingContext& renderingContext)
    {
        m_GraphicsWrapper->EndFrame();
        renderingContext.m_GraphicsWrapper = nullptr;
        renderingContext.m_DefaultShader = nullptr;
        renderingContext.m_CurrentShader = nullptr;
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