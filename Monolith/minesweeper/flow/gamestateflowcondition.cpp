#include <precomp.h>
#include <minesweeper/flow/gamestateflowcondition.h>

#include <core/serialization/objectserializer.h>

namespace Monolith
{
#pragma region GeneratedCodeSource
    GameStateFlowConditionData::GameStateFlowConditionData()
        : super{}
    {
    }

    GameStateFlowConditionData::~GameStateFlowConditionData()
    {
    }

    void GameStateFlowConditionData::LoadObject(const ObjectSerializer& serializer)
    {
        super::LoadObject(serializer);
    }
#pragma endregion //GeneratedCodeSource

    FlowCondition* GameStateFlowConditionData::InstantiateFlowCondition() const
    {
        return new GameStateFlowCondition{ *this };
    }



    GameStateFlowCondition::GameStateFlowCondition(const GameStateFlowConditionData& gameStateFlowConditioneData)
        : FlowCondition{ gameStateFlowConditioneData }
    {
    }

    bool GameStateFlowCondition::IsSatisfied() const
    {
        return false;
    }
}
