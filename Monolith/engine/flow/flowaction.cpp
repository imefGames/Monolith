#include <precomp.h>
#include <engine/flow/flowaction.h>

#include <core/serialization/objectserializer.h>

namespace Monolith
{
#pragma region GeneratedCodeSource
    FlowActionData::FlowActionData()
        : super{}
    {
    }

    FlowActionData::~FlowActionData()
    {
    }

    void FlowActionData::LoadObject(const ObjectSerializer& serializer)
    {
        super::LoadObject(serializer);
    }
#pragma endregion //GeneratedCodeSource

    FlowAction* FlowActionData::InstantiateFlowAction() const
    {
        return new FlowAction{ *this };
    }



    FlowAction::FlowAction(const FlowActionData& flowActionData)
    {
    }
}
