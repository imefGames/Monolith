#pragma once

#include <engine/flow/flowcondition.h>
#include <engine/model/object.h>
#include <vector>

namespace Monolith
{
    class FlowCondtion;
    class FlowCondtionData;
    class FlowTransition;

    using FlowConditionInitDataArray = std::vector<FlowConditionData*>;
    using FlowConditionInitDataOutputArray = const std::vector<FlowConditionData*>&;

#pragma region GeneratedCodeHeader
    class FlowTransitionData : public Object
    {
    public:
        FlowTransitionData();
        ~FlowTransitionData();

        void LoadObject(const ObjectSerializer& serializer) override;

        u32 GetDestinationStateID() const { return m_DestinationStateID; }
        void SetDestinationStateID(u32 newValue) { m_DestinationStateID = newValue; }

        FlowTransition* InstanciateFlowTransition() const;
        FlowConditionInitDataOutputArray GetFlowConditions() const;

    private:
        using super = Object;

        u32 m_DestinationStateID;
        FlowConditionInitDataArray m_FlowConditions;
    };
#pragma endregion //GeneratedCodeHeader

    class FlowTransition
    {
    public:
        FlowTransition(const FlowTransitionData& flowTransitionData);
        ~FlowTransition();

        bool CanChangeState() const;
        inline u32 GetDestinationStateID() const { return m_DestinationStateID; }

    private:
        std::vector<FlowCondition*> m_Conditions;
        u32 m_DestinationStateID;
    };
}
