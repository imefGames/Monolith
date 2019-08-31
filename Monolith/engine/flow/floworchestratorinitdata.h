#pragma once

#include <engine/flow/flowstate.h>
#include <engine/model/data/gamesysteminitdata.h>

namespace Monolith
{
    using FlowStateDataArray = std::vector<FlowStateData>;
    using FlowStateDataOutputArray = const std::vector<FlowStateData>&;

#pragma region GeneratedCodeHeader
    class FlowOrchestratorInitData : public GameSystemInitData
    {
    public:
        FlowOrchestratorInitData();
        ~FlowOrchestratorInitData();

        void LoadObject(const ObjectSerializer& serializer) override;

        u32 GetStartupStateID() const { return m_StartupStateID; }
        void SetStartupStateID(u32 newValue) { m_StartupStateID = newValue; }

        GameSystem* InstanciateGameSystem() const override;
        FlowStateDataOutputArray GetStates() const;

    private:
        using super = GameSystemInitData;

        u32 m_StartupStateID;
        FlowStateDataArray m_States;
    };
#pragma endregion //GeneratedCodeHeader
}
