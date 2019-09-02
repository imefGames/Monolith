#pragma once

#include <engine/model/gamesystem.h>
#include <engine/model/data/gamesysteminitdata.h>

namespace Monolith
{
#pragma region GeneratedCodeHeader
    class MinesweeperGameSystemInitData : public GameSystemInitData
    {
    public:
        MinesweeperGameSystemInitData();
        ~MinesweeperGameSystemInitData();

        void LoadObject(const ObjectSerializer& serializer) override;


        GameSystem* InstantiateGameSystem() const override;

    private:
        using super = GameSystemInitData;

    };
#pragma endregion //GeneratedCodeHeader

    class MinesweeperGameSystem : public GameSystem
    {
    public:
        MinesweeperGameSystem(const MinesweeperGameSystemInitData& minesweeperGameSystemInitData);
    };
}
