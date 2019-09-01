#pragma once

#include <core/singleton.h>
#include <engine/model/gamesystem.h>
#include <engine/flow/flowstate.h>
#include <engine/flow/flowstatecontext.h>
#include <vector>

namespace Monolith
{
    class FlowOrchestratorInitData;

    class FlowOrchestrator : public GameSystem, public Singleton<FlowOrchestrator>
    {
    public:
        FlowOrchestrator(const FlowOrchestratorInitData& initData);

        bool IsGameRunning() const;

    protected:
        void OnInit() override;
        void OnShutdown() override;
        void OnUpdate(f32 dt) override;

    private:
        FlowState* GetNextState() const;

        FlowStateContext m_StateContext;
        std::vector<FlowState*> m_States;
        FlowState* m_CurrentState;
    };

    namespace FlowHelper
    {
        bool IsGameRunning();
    }
}