#pragma once

#include <core/singleton.h>
#include <engine/model/gamesystem.h>
#include <engine/rendering/graphicdevicedata.h>
#include <engine/rendering/renderpass.h>
#include <engine/rendering/textureloader.h>
#include <engine/rendering/shaders/shaderinitdata.h>

namespace Monolith
{
    class Font;
    class GameRendererInitData;
    class GameWindowData;
    class GraphicsWrapper;
    class RenderingContext;
    class Shader;
    class TextureHandle;

    class GameRenderer : public GameSystem, public Singleton<GameRenderer>
    {
    public:
        GameRenderer(const GameRendererInitData& initData);

        inline TextureLoader& GetTextureLoader() { return m_TextureLoader; }
        inline const GraphicDeviceData& GetGraphicDeviceData() const { return m_GraphicDeviceData; }

        void InitGraphics(const GameWindowData& gameWindowData);
        void ShutdownGraphics();
        void StartFrame(RenderingContext& renderingContext);
        void RenderAllPasses(RenderingContext& renderingContext);
        void EndFrame(RenderingContext& renderingContext);

    protected:
        void OnInit() override;
        void OnShutdown() override;

    private:
        std::vector<RenderPass*> m_RenderPasses;
        TextureLoader m_TextureLoader;
        GraphicsWrapper* m_GraphicsWrapper;
        GraphicDeviceData m_GraphicDeviceData;
        ShaderInitData m_DefaultShaderInitData;
        Shader* m_DefaultShader;
        TextureHandle* m_DefaultTexture;
        Font* m_DefaultFont;
    };

    namespace RenderingHelper
    {
        void StartFrame(RenderingContext& renderingContext);
        void RenderAllPasses(RenderingContext& renderingContext);
        void EndFrame(RenderingContext& renderingContext);
        void InitGraphics(const GameWindowData& gameWindowData);
        void ShutdownGraphics();
    }
}
