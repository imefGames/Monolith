#pragma once

#include <engine/flow/flowcondition.h>

namespace Monolith
{
    class GameStateFlowCondition;
    enum class EMinesweeperGameState;

#pragma region GeneratedCodeHeader
    class GameStateFlowConditionData : public FlowConditionData
    {
    public:
        GameStateFlowConditionData();
        ~GameStateFlowConditionData();

        void LoadObject(const ObjectSerializer& serializer) override;

        u32 GetExpectedState() const { return m_ExpectedState; }
        void SetExpectedState(u32 newValue) { m_ExpectedState = newValue; }

        FlowCondition* InstantiateFlowCondition() const override;

    private:
        using super = FlowConditionData;

        u32 m_ExpectedState;
    };
#pragma endregion //GeneratedCodeHeader

    class GameStateFlowCondition : public FlowCondition
    {
    public:
        GameStateFlowCondition(const GameStateFlowConditionData& gameStateFlowConditionData);

        bool IsSatisfied() const override;

    private:
        EMinesweeperGameState m_ExpectedState;
    };
}
