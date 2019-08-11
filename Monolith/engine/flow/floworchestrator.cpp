#include <precomp.h>
#include <engine/flow/floworchestrator.h>

namespace Monolith
{
    void FlowOrchestrator::OnInit()
    {
        RegisterInstance(this);
    }

    void FlowOrchestrator::OnShutdown()
    {
        UnregisterInstance(this);
    }

    bool FlowOrchestrator::IsGameRunning() const
    {
        return true;
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