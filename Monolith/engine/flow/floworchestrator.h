#pragma once

#include <core/singleton.h>
#include <engine/model/gamesystem.h>

namespace Monolith
{
    class FlowOrchestrator : public GameSystem, public Singleton<FlowOrchestrator>
    {
    public:
        FlowOrchestrator();
        ~FlowOrchestrator();

        bool IsGameRunning() const;
    };

    namespace FlowHelper
    {
        bool IsGameRunning();
    }
}