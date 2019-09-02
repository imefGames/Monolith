#include <precomp.h>
#include <engine/flow/flowstate.h>

#include <core/serialization/objectserializer.h>
#include <engine/flow/flowaction.h>
#include <engine/flow/flowstatecontext.h>
#include <engine/flow/flowtransition.h>

namespace Monolith
{
#pragma region GeneratedCodeSource
    FlowStateData::FlowStateData()
        : super{}
        , m_StateID{ u32Max }
        , m_OnEnterActions{  }
        , m_OnExitActions{  }
        , m_OnUpdateActions{  }
        , m_Transitions{  }
    {
    }

    FlowStateData::~FlowStateData()
    {
        ObjectHelper::Delete(m_OnEnterActions);
        ObjectHelper::Delete(m_OnExitActions);
        ObjectHelper::Delete(m_OnUpdateActions);
    }

    void FlowStateData::LoadObject(const ObjectSerializer& serializer)
    {
        super::LoadObject(serializer);
        ObjectSerializationHelper::LoadObject(serializer["StateID"], m_StateID);
        ObjectSerializationHelper::LoadObject(serializer["OnEnterActions"], m_OnEnterActions);
        ObjectSerializationHelper::LoadObject(serializer["OnExitActions"], m_OnExitActions);
        ObjectSerializationHelper::LoadObject(serializer["OnUpdateActions"], m_OnUpdateActions);
        ObjectSerializationHelper::LoadObject(serializer["Transitions"], m_Transitions);
    }
#pragma endregion //GeneratedCodeSource

    FlowState* FlowStateData::InstantiateFlowState() const
    {
        return new FlowState{ *this };
    }

    FlowActionInitDataOutputArray FlowStateData::GetOnEnterActions() const
    {
        return m_OnEnterActions;
    }

    FlowActionInitDataOutputArray FlowStateData::GetOnExitActions() const
    {
        return m_OnExitActions;
    }

    FlowActionInitDataOutputArray FlowStateData::GetOnUpdateActions() const
    {
        return m_OnUpdateActions;
    }

    FlowTransitionInitDataOutputArray FlowStateData::GetTransitions() const
    {
        return m_Transitions;
    }



    FlowState::FlowState(const FlowStateData& flowStateData)
        : m_StateID{ flowStateData.GetStateID() }
    {
        InitActionList(m_OnEnterActions, flowStateData.GetOnEnterActions());
        InitActionList(m_OnExitActions, flowStateData.GetOnExitActions());
        InitActionList(m_OnUpdateActions, flowStateData.GetOnUpdateActions());
        InitTransitionList(m_Transitions, flowStateData.GetTransitions());
    }

    FlowState::~FlowState()
    {
        ShutdownActionList(m_OnEnterActions);
        ShutdownActionList(m_OnExitActions);
        ShutdownActionList(m_OnUpdateActions);
        ShutdownTransitionList(m_Transitions);
    }

    void FlowState::Enter()
    {
        for (const FlowAction* action : m_OnEnterActions)
        {
            action->Execute();
        }
    }

    void FlowState::Exit()
    {
        for (const FlowAction* action : m_OnExitActions)
        {
            action->Execute();
        }
    }

    void FlowState::Update(FlowStateContext& context)
    {
        for (const FlowAction* action : m_OnUpdateActions)
        {
            action->Execute();
        }

        for (const FlowTransition* transition : m_Transitions)
        {
            if (transition->CanChangeState())
            {
                context.SetNextStateID(transition->GetDestinationStateID());
            }
        }
    }

    void FlowState::InitActionList(std::vector<FlowAction*>& actions, const std::vector<FlowActionData*>& actionsData) const
    {
        actions.reserve(actionsData.size());
        for (const FlowActionData* actionData : actionsData)
        {
            actions.push_back(actionData->InstantiateFlowAction());
        }
    }

    void FlowState::InitTransitionList(std::vector<FlowTransition*>& transitions, const std::vector<FlowTransitionData>& transitionsData) const
    {
        transitions.reserve(transitionsData.size());
        for (const FlowTransitionData& transitionData : transitionsData)
        {
            transitions.push_back(transitionData.InstantiateFlowTransition());
        }
    }

    void FlowState::ShutdownActionList(std::vector<FlowAction*>& actions) const
    {
        for (FlowAction* action : actions)
        {
            delete action;
        }
        actions.clear();
    }

    void FlowState::ShutdownTransitionList(std::vector<FlowTransition*>& transitions) const
    {
        for (FlowTransition* transition : transitions)
        {
            delete transition;
        }
        transitions.clear();
    }
}
