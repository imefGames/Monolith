#include <precomp.h>
#include <engine/flow/floworchestrator.h>

namespace Monolith
{
    FlowOrchestrator::FlowOrchestrator()
        : GameSystem{}
    {
        RegisterInstance(this);
    }

    FlowOrchestrator::~FlowOrchestrator()
    {
        UnregisterInstance(this);
    }

    bool FlowOrchestrator::IsGameRunning() const
    {
        return false;
    }

    namespace FlowHelper
    {
        bool IsGameRunning()
        {
            FlowOrchestrator* flowOrchestrator{ FlowOrchestrator::Get() };
            return (flowOrchestrator != nullptr && flowOrchestrator->IsGameRunning());
        }
    }
}