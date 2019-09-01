#include <precomp.h>
#include <engine/flow/floworchestrator.h>

#include <engine/flow/floworchestratorinitdata.h>
#include <algorithm>

namespace Monolith
{
    FlowOrchestrator::FlowOrchestrator(const FlowOrchestratorInitData& initData)
        : m_CurrentState{ nullptr }
    {
        m_StateContext.SetNextStateID(initData.GetStartupStateID());

        const std::vector<FlowStateData>& statesData{ initData.GetStates() };
        m_States.reserve(statesData.size());
        for (const FlowStateData& stateData : statesData)
        {
            m_States.push_back(stateData.InstanciateFlowState());
        }
    }

    void FlowOrchestrator::OnInit()
    {
        RegisterInstance(this);
    }

    void FlowOrchestrator::OnShutdown()
    {
        UnregisterInstance(this);
    }

    void FlowOrchestrator::OnUpdate(f32 dt)
    {
        FlowState* nextState{ m_CurrentState };
        if (m_CurrentState == nullptr || m_CurrentState->GetStateID() != m_StateContext.GetNextStateID())
        {
            nextState = GetNextState();
        }

        if (nextState != m_CurrentState)
        {
            if (m_CurrentState != nullptr)
            {
                m_CurrentState->Exit();
            }
            if (nextState != nullptr)
            {
                nextState->Enter();
            }
            m_CurrentState = nextState;
        }

        if (m_CurrentState != nullptr)
        {
            m_CurrentState->Update(m_StateContext);
        }
    }

    FlowState* FlowOrchestrator::GetNextState() const
    {
        u32 nextStateID{ m_StateContext.GetNextStateID() };
        auto findByID{ [nextStateID](FlowState* state) { return state->GetStateID() == nextStateID; } };
        auto foundIt{ std::find_if(m_States.begin(), m_States.end(), findByID) };
        return (foundIt != m_States.end() ? *foundIt : nullptr);
    }

    bool FlowOrchestrator::IsGameRunning() const
    {
        return m_StateContext.GetNextStateID() != u32Max;
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