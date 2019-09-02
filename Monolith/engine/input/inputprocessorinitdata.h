#pragma once

#include <engine/model/data/gamesysteminitdata.h>

namespace Monolith
{
#pragma region GeneratedCodeHeader
    class InputProcessorInitData : public GameSystemInitData
    {
    public:
        InputProcessorInitData();
        ~InputProcessorInitData();

        void LoadObject(const ObjectSerializer& serializer) override;


        GameSystem* InstantiateGameSystem() const override;

    private:
        using super = GameSystemInitData;

    };
#pragma endregion //GeneratedCodeHeader
}
