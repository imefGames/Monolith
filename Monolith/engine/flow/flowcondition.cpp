#include <precomp.h>
#include <engine/flow/flowcondition.h>

#include <core/serialization/objectserializer.h>

namespace Monolith
{
#pragma region GeneratedCodeSource
    FlowConditionData::FlowConditionData()
        : super{}
    {
    }

    FlowConditionData::~FlowConditionData()
    {
    }

    void FlowConditionData::LoadObject(const ObjectSerializer& serializer)
    {
        super::LoadObject(serializer);
    }
#pragma endregion //GeneratedCodeSource

    FlowCondition* FlowConditionData::InstantiateFlowCondition() const
    {
        return new FlowCondition{ *this };
    }



    FlowCondition::FlowCondition(const FlowConditionData& flowConditioneData)
    {
    }
}
