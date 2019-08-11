#pragma once

#include <core/singleton.h>
#include <engine/model/gamesystem.h>

namespace Monolith
{
    class RenderingContext;

    class GameRenderer : public GameSystem, public Singleton<GameRenderer>
    {
    public:
        void StartFrame(RenderingContext& inputEvents);
        void EndFrame(RenderingContext& inputEvents);

    protected:
        void OnInit() override;
        void OnShutdown() override;
    };

    namespace RenderingHelper
    {
        void StartFrame(RenderingContext& inputEvents);
        void EndFrame(RenderingContext& inputEvents);
    }
}
