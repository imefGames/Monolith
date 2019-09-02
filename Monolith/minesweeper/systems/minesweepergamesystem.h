#pragma once

#include <core/singleton.h>
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

    enum class EMinesweeperGameState
    {
        TitlePage,
        InGame,
        Exit
    };

    class MinesweeperGameSystem : public GameSystem, public Singleton<MinesweeperGameSystem>
    {
    public:
        MinesweeperGameSystem(const MinesweeperGameSystemInitData& minesweeperGameSystemInitData);

        inline EMinesweeperGameState GetGameState() { return m_GameState; }
        inline void SetGameState(EMinesweeperGameState newState) { m_GameState = newState; }

    protected:
        void OnInit() override;
        void OnShutdown() override;

    private:
        EMinesweeperGameState m_GameState;
    };
}
