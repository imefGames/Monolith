#pragma once

#include <core/singleton.h>
#include <engine/model/gamesystem.h>
#include <engine/rendering/graphicdevicedata.h>
#include <engine/rendering/shaders/shaderinitdata.h>

namespace Monolith
{
    class GameRendererInitData;
    class GameWindowData;
    class GraphicsWrapper;
    class RenderingContext;
    class Shader;
    class Texture;

    class GameRenderer : public GameSystem, public Singleton<GameRenderer>
    {
    public:
        GameRenderer(const GameRendererInitData& initData);

        inline const GraphicDeviceData& GetGraphicDeviceData() const { return m_GraphicDeviceData; }

        void InitGraphics(const GameWindowData& gameWindowData);
        void ShutdownGraphics();
        void StartFrame(RenderingContext& inputEvents);
        void EndFrame(RenderingContext& inputEvents);

    protected:
        void OnInit() override;
        void OnShutdown() override;

    private:
        GraphicsWrapper* m_GraphicsWrapper;
        GraphicDeviceData m_GraphicDeviceData;
        ShaderInitData m_DefaultShaderInitData;
        Shader* m_DefaultShader;
        Texture* m_Texture;
    };

    namespace RenderingHelper
    {
        void StartFrame(RenderingContext& inputEvents);
        void EndFrame(RenderingContext& inputEvents);
        void InitGraphics(const GameWindowData& gameWindowData);
        void ShutdownGraphics();
    }
}
