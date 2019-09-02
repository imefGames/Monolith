#pragma once

#include <engine/model/object.h>
#include <vector>

namespace Monolith
{
    class GameSystem;
    class GameSystemInitData;

    using GameSystemOutputArray = std::vector<GameSystem*>&;
    using GameSystemInitDataArray = std::vector<GameSystemInitData*>;

#pragma region GeneratedCodeHeader
    class UniverseInitData : public Object
    {
    public:
        UniverseInitData();
        ~UniverseInitData();

        void LoadObject(const ObjectSerializer& serializer) override;


        void InstantiateGameSystems(GameSystemOutputArray gameSystems) const;

    private:
        using super = Object;

        GameSystemInitDataArray m_GameSystems;
    };
#pragma endregion //GeneratedCodeHeader
}
