#include <precomp.h>
#include <engine/rendering/gamerenderer.h>

#include <engine/rendering/font.h>
#include <engine/rendering/gamerendererinitdata.h>
#include <engine/rendering/graphicswrapper.h>
#include <engine/rendering/renderingcontext.h>
#include <engine/rendering/texturehandle.h>
#include <engine/rendering/shaders/shader.h>
#include <engine/window/gamewindowdata.h>

#include <Windows.h>

namespace Monolith
{
    const bool K_FULL_SCREEN = false;
    const bool K_VSYNC_ENABLED = true;

    GameRenderer::GameRenderer(const GameRendererInitData& initData)
        : m_GraphicsWrapper{ nullptr }
        , m_DefaultShader{ nullptr }
        , m_DefaultTexture{ nullptr }
        , m_DefaultFont{ nullptr }
        , m_DefaultShaderInitData{ initData.GetDefaultShader() }
    {
        m_RenderPasses.reserve(initData.GetRenderPasses().size());
        for (const RenderPassInitData& renderPassData : initData.GetRenderPasses())
        {
            m_RenderPasses.push_back(renderPassData.InstantiateRenderPass());
        }
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

        m_DefaultTexture = new TextureHandle{ "minesweeper/textures/default.png" };
        m_DefaultFont = new Font{ "minesweeper/textures/defaultFont.png", "minesweeper/textures/defaultFontData.txt" };
    }

    void GameRenderer::ShutdownGraphics()
    {
        for (RenderPass* renderPass : m_RenderPasses)
        {
            delete renderPass;
        }
        m_RenderPasses.clear();

        m_DefaultShader->Shutdown();
        delete m_DefaultShader;
        m_DefaultShader = nullptr;

        m_GraphicsWrapper->Shutdown();
        delete m_GraphicsWrapper;
        m_GraphicsWrapper = nullptr;

        delete m_DefaultTexture;
        m_DefaultTexture = nullptr;

        delete m_DefaultFont;
        m_DefaultFont = nullptr;
    }

    void GameRenderer::StartFrame(RenderingContext& renderingContext)
    {
        m_TextureLoader.LoadPendingTextures();

        renderingContext.m_Camera.SetFromPosition(Vec4f{ 0.0f, 0.0f, -10.0f });
        renderingContext.m_GraphicsWrapper = m_GraphicsWrapper;
        renderingContext.m_Camera.ComputeViewMatrix();
        renderingContext.m_ViewMatrix = renderingContext.m_Camera.GetViewMatrix();
        renderingContext.m_WorldMatrix = Mat44f::GetIdentity();
        renderingContext.m_DefaultShader = m_DefaultShader;
        renderingContext.m_CurrentShader = renderingContext.m_DefaultShader;
        renderingContext.SetTexture(*m_DefaultTexture);
        renderingContext.SetFont(m_DefaultFont);

        m_GraphicsWrapper->BeginFrame();
    }

    void GameRenderer::RenderAllPasses(RenderingContext& renderingContext)
    {
        for (RenderPass* renderPass : m_RenderPasses)
        {
            renderPass->Render(renderingContext);
        }
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

        void RenderAllPasses(RenderingContext& renderingContext)
        {
            GameRenderer* gameRenderer{ GameRenderer::Get() };
            if (gameRenderer != nullptr)
            {
                gameRenderer->RenderAllPasses(renderingContext);
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