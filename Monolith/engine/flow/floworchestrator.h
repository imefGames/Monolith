#pragma once

#include <core/singleton.h>
#include <engine/model/gamesystem.h>

namespace Monolith
{
    class FlowOrchestrator : public GameSystem, public Singleton<FlowOrchestrator>
    {
    public:
        bool IsGameRunning() const;

    protected:
        void OnInit() override;
        void OnShutdown() override;
    };

    namespace FlowHelper
    {
        bool IsGameRunning();
    }
}