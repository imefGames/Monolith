#include <precomp.h>
#include <minesweeper/flow/gamestateflowcondition.h>

#include <core/serialization/objectserializer.h>
#include <minesweeper/systems/minesweepergamesystem.h>

namespace Monolith
{
#pragma region GeneratedCodeSource
    GameStateFlowConditionData::GameStateFlowConditionData()
        : super{}
        , m_ExpectedState{ 0 }
    {
    }

    GameStateFlowConditionData::~GameStateFlowConditionData()
    {
    }

    void GameStateFlowConditionData::LoadObject(const ObjectSerializer& serializer)
    {
        super::LoadObject(serializer);
        ObjectSerializationHelper::LoadObject(serializer["ExpectedState"], m_ExpectedState);
    }
#pragma endregion //GeneratedCodeSource

    FlowCondition* GameStateFlowConditionData::InstantiateFlowCondition() const
    {
        return new GameStateFlowCondition{ *this };
    }



    GameStateFlowCondition::GameStateFlowCondition(const GameStateFlowConditionData& gameStateFlowConditioneData)
        : FlowCondition{ gameStateFlowConditioneData }
        , m_ExpectedState{ static_cast<EMinesweeperGameState>(gameStateFlowConditioneData.GetExpectedState()) }
    {
    }

    bool GameStateFlowCondition::IsSatisfied() const
    {
        return (MinesweeperGameSystem::Get()->GetGameState() == m_ExpectedState);
    }
}
