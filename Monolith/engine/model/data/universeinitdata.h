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

        std::string GetStartupWorld() const { return m_StartupWorld; }
        void SetStartupWorld(std::string newValue) { m_StartupWorld = newValue; }

        void InstantiateGameSystems(GameSystemOutputArray gameSystems) const;

    private:
        using super = Object;

        GameSystemInitDataArray m_GameSystems;
        std::string m_StartupWorld;
    };
#pragma endregion //GeneratedCodeHeader
}
