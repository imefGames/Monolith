#include <precomp.h>
#include <minesweeper/systems/minesweepergamesystem.h>

#include <core/serialization/objectserializer.h>

namespace Monolith
{
#pragma region GeneratedCodeSource
    MinesweeperGameSystemInitData::MinesweeperGameSystemInitData()
        : super{}
    {
    }

    MinesweeperGameSystemInitData::~MinesweeperGameSystemInitData()
    {
    }

    void MinesweeperGameSystemInitData::LoadObject(const ObjectSerializer& serializer)
    {
        super::LoadObject(serializer);
    }
#pragma endregion //GeneratedCodeSource

    GameSystem* MinesweeperGameSystemInitData::InstantiateGameSystem() const
    {
        return new MinesweeperGameSystem{ *this };
    }



    MinesweeperGameSystem::MinesweeperGameSystem(const MinesweeperGameSystemInitData& minesweeperGameSystemInitData)
    {
    }
}
