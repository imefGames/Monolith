#pragma once

#include <engine/flow/flowcondition.h>

namespace Monolith
{
    class GameStateFlowCondition;

#pragma region GeneratedCodeHeader
    class GameStateFlowConditionData : public FlowConditionData
    {
    public:
        GameStateFlowConditionData();
        ~GameStateFlowConditionData();

        void LoadObject(const ObjectSerializer& serializer) override;


        FlowCondition* InstantiateFlowCondition() const override;

    private:
        using super = FlowConditionData;

    };
#pragma endregion //GeneratedCodeHeader

    class GameStateFlowCondition : public FlowCondition
    {
    public:
        GameStateFlowCondition(const GameStateFlowConditionData& gameStateFlowConditionData);

        bool IsSatisfied() const override;
    };
}
