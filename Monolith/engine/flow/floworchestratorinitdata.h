#pragma once

#include <engine/model/data/gamesysteminitdata.h>

namespace Monolith
{
#pragma region GeneratedCodeHeader
    class FlowOrchestratorInitData : public GameSystemInitData
    {
    public:
        FlowOrchestratorInitData();
        ~FlowOrchestratorInitData();

        void LoadObject(const ObjectSerializer& serializer) override;


        GameSystem* InstanciateGameSystem() const override;

    private:
        using super = GameSystemInitData;

    };
#pragma endregion //GeneratedCodeHeader
}
