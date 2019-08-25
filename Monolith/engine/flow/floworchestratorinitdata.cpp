#include <precomp.h>
#include <engine/flow/floworchestratorinitdata.h>

#include <core/serialization/objectserializer.h>
#include <engine/flow/floworchestrator.h>

namespace Monolith
{
#pragma region GeneratedCodeSource
    FlowOrchestratorInitData::FlowOrchestratorInitData()
        : super{}
    {
    }

    FlowOrchestratorInitData::~FlowOrchestratorInitData()
    {
    }

    void FlowOrchestratorInitData::LoadObject(const ObjectSerializer& serializer)
    {
        super::LoadObject(serializer);
    }
#pragma endregion //GeneratedCodeSource

    GameSystem* FlowOrchestratorInitData::InstanciateGameSystem() const
    {
        return new FlowOrchestrator();
    }
}
