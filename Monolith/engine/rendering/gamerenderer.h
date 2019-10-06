#pragma once

#include <core/singleton.h>
#include <engine/model/gamesystem.h>
#include <engine/rendering/graphicdevicedata.h>

namespace Monolith
{
    class RenderingContext;
    class GameWindowData;
    class GraphicsWrapper;

    class GameRenderer : public GameSystem, public Singleton<GameRenderer>
    {
    public:
        GameRenderer();

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
    };

    namespace RenderingHelper
    {
        void StartFrame(RenderingContext& inputEvents);
        void EndFrame(RenderingContext& inputEvents);
        void InitGraphics(const GameWindowData& gameWindowData);
        void ShutdownGraphics();
    }
}
