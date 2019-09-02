#include <precomp.h>
#include <engine/flow/actions/gotoworldflowaction.h>

#include <core/serialization/objectserializer.h>
#include <engine/model/universe.h>

namespace Monolith
{
#pragma region GeneratedCodeSource
    GoToWorldFlowActionData::GoToWorldFlowActionData()
        : super{}
        , m_DestinationWorld{  }
    {
    }

    GoToWorldFlowActionData::~GoToWorldFlowActionData()
    {
    }

    void GoToWorldFlowActionData::LoadObject(const ObjectSerializer& serializer)
    {
        super::LoadObject(serializer);
        ObjectSerializationHelper::LoadObject(serializer["DestinationWorld"], m_DestinationWorld);
    }
#pragma endregion //GeneratedCodeSource

    FlowAction* GoToWorldFlowActionData::InstantiateFlowAction() const
    {
        return new GoToWorldFlowAction{ *this };
    }



    GoToWorldFlowAction::GoToWorldFlowAction(const GoToWorldFlowActionData& goToWorldFlowActionData)
        : FlowAction{ goToWorldFlowActionData }
        , m_DestinationWorld{ goToWorldFlowActionData.GetDestinationWorld() }
    {
    }

    void GoToWorldFlowAction::Execute() const
    {
        Universe::Get()->GoToWorld(m_DestinationWorld);
    }
}
