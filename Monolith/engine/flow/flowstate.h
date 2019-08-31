#pragma once

#include <engine/flow/flowtransition.h>
#include <engine/model/object.h>
#include <vector>

namespace Monolith
{
    class FlowAction;
    class FlowActionData;
    class FlowState;
    class FlowStateContext;

    using FlowActionInitDataArray = std::vector<FlowActionData*>;
    using FlowTransitionInitDataArray = std::vector<FlowTransitionData>;
    using FlowActionInitDataOutputArray = const std::vector<FlowActionData*>&;
    using FlowTransitionInitDataOutputArray = const std::vector<FlowTransitionData>&;

#pragma region GeneratedCodeHeader
    class FlowStateData : public Object
    {
    public:
        FlowStateData();
        ~FlowStateData();

        void LoadObject(const ObjectSerializer& serializer) override;

        u32 GetStateID() const { return m_StateID; }
        void SetStateID(u32 newValue) { m_StateID = newValue; }

        FlowState* InstanciateFlowState() const;
        FlowActionInitDataOutputArray GetOnEnterActions() const;
        FlowActionInitDataOutputArray GetOnExitActions() const;
        FlowActionInitDataOutputArray GetOnUpdateActions() const;
        FlowTransitionInitDataOutputArray GetTransitions() const;

    private:
        using super = Object;

        u32 m_StateID;
        FlowActionInitDataArray m_OnEnterActions;
        FlowActionInitDataArray m_OnExitActions;
        FlowActionInitDataArray m_OnUpdateActions;
        FlowTransitionInitDataArray m_Transitions;
    };
#pragma endregion //GeneratedCodeHeader

    class FlowState
    {
    public:
        FlowState(const FlowStateData& flowStateData);
        ~FlowState();

        void Enter();
        void Exit();
        void Update(FlowStateContext& context);

    private:
        void InitActionList(std::vector<FlowAction*>& actions, const std::vector<FlowActionData*>& actionsData) const;
        void InitTransitionList(std::vector<FlowTransition*>& transitions, const std::vector<FlowTransitionData>& transitionsData) const;
        void ShutdownActionList(std::vector<FlowAction*>& actions) const;
        void ShutdownTransitionList(std::vector<FlowTransition*>& transitions) const;

        u32 m_StateID;
        std::vector<FlowAction*> m_OnEnterActions;
        std::vector<FlowAction*> m_OnExitActions;
        std::vector<FlowAction*> m_OnUpdateActions;
        std::vector<FlowTransition*> m_Transitions;
    };
}
