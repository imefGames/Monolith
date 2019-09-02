#pragma once

#include <engine/flow/flowaction.h>
#include <string>

namespace Monolith
{
#pragma region GeneratedCodeHeader
    class GoToWorldFlowActionData : public FlowActionData
    {
    public:
        GoToWorldFlowActionData();
        ~GoToWorldFlowActionData();

        void LoadObject(const ObjectSerializer& serializer) override;

        std::string GetDestinationWorld() const { return m_DestinationWorld; }
        void SetDestinationWorld(std::string newValue) { m_DestinationWorld = newValue; }

        FlowAction* InstantiateFlowAction() const override;

    private:
        using super = FlowActionData;

        std::string m_DestinationWorld;
    };
#pragma endregion //GeneratedCodeHeader

    class GoToWorldFlowAction : public FlowAction
    {
    public:
        GoToWorldFlowAction(const GoToWorldFlowActionData& GoToWorldFlowActionData);

        void Execute() const override;

    private:
        std::string m_DestinationWorld;
    };
}
