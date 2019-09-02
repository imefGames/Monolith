#include <precomp.h>
#include <engine/flow/flowtransition.h>

#include <core/serialization/objectserializer.h>
#include <algorithm>

namespace Monolith
{
#pragma region GeneratedCodeSource
    FlowTransitionData::FlowTransitionData()
        : super{}
        , m_DestinationStateID{ u32Max }
        , m_FlowConditions{  }
    {
    }

    FlowTransitionData::~FlowTransitionData()
    {
        ObjectHelper::Delete(m_FlowConditions);
    }

    void FlowTransitionData::LoadObject(const ObjectSerializer& serializer)
    {
        super::LoadObject(serializer);
        ObjectSerializationHelper::LoadObject(serializer["DestinationStateID"], m_DestinationStateID);
        ObjectSerializationHelper::LoadObject(serializer["FlowConditions"], m_FlowConditions);
    }
#pragma endregion //GeneratedCodeSource

    FlowTransition* FlowTransitionData::InstantiateFlowTransition() const
    {
        return new FlowTransition{ *this };
    }

    FlowConditionInitDataOutputArray FlowTransitionData::GetFlowConditions() const
    {
        return m_FlowConditions;
    }



    FlowTransition::FlowTransition(const FlowTransitionData& flowTransitionData)
        : m_DestinationStateID{ flowTransitionData.GetDestinationStateID() }
    {
        FlowConditionInitDataOutputArray flowConditions{ flowTransitionData.GetFlowConditions() };
        m_Conditions.reserve(flowConditions.size());
        for (const FlowConditionData* conditionData : flowConditions)
        {
            m_Conditions.push_back(conditionData->InstantiateFlowCondition());
        }
    }

    FlowTransition::~FlowTransition()
    {
        for (FlowCondition* condition : m_Conditions)
        {
            delete condition;
        }
        m_Conditions.clear();
    }

    bool FlowTransition::CanChangeState() const
    {
        auto findStatisfiedCondition{ [](const FlowCondition* condition) { return condition->IsSatisfied(); } };
        return std::all_of(m_Conditions.begin(), m_Conditions.end(), findStatisfiedCondition);
    }
}
