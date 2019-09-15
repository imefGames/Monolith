#pragma once

#include <core/singleton.h>
#include <engine/model/gamesystem.h>

namespace Monolith
{
    class RenderingContext;
    class GameWindowData;
    class GraphicsWrapper;

    class GameRenderer : public GameSystem, public Singleton<GameRenderer>
    {
    public:
        GameRenderer();

        void InitGraphics(const GameWindowData& gameWindowData);
        void ShutdownGraphics();
        void StartFrame(RenderingContext& inputEvents);
        void EndFrame(RenderingContext& inputEvents);

    protected:
        void OnInit() override;
        void OnShutdown() override;

    private:
        GraphicsWrapper* m_GraphicsWrapper;
    };

    namespace RenderingHelper
    {
        void StartFrame(RenderingContext& inputEvents);
        void EndFrame(RenderingContext& inputEvents);
        void InitGraphics(const GameWindowData& gameWindowData);
        void ShutdownGraphics();
    }
}
