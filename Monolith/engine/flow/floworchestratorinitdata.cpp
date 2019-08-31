#include <precomp.h>
#include <engine/flow/floworchestratorinitdata.h>

#include <core/serialization/objectserializer.h>
#include <engine/flow/floworchestrator.h>

namespace Monolith
{
#pragma region GeneratedCodeSource
    FlowOrchestratorInitData::FlowOrchestratorInitData()
        : super{}
        , m_StartupStateID{ u32Max }
        , m_States{  }
    {
    }

    FlowOrchestratorInitData::~FlowOrchestratorInitData()
    {
    }

    void FlowOrchestratorInitData::LoadObject(const ObjectSerializer& serializer)
    {
        super::LoadObject(serializer);
        ObjectSerializationHelper::LoadObject(serializer["StartupStateID"], m_StartupStateID);
        ObjectSerializationHelper::LoadObject(serializer["States"], m_States);
    }
#pragma endregion //GeneratedCodeSource

    GameSystem* FlowOrchestratorInitData::InstanciateGameSystem() const
    {
        return new FlowOrchestrator();
    }

    FlowStateDataOutputArray FlowOrchestratorInitData::GetStates() const
    {
        return m_States;
    }
}
