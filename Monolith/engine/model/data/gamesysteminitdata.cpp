#include <precomp.h>
#include <engine/model/data/gamesysteminitdata.h>

#include <core/serialization/objectserializer.h>

namespace Monolith
{
#pragma region GeneratedCodeSource
    GameSystemInitData::GameSystemInitData()
        : super{}
    {
    }

    GameSystemInitData::~GameSystemInitData()
    {
    }

    void GameSystemInitData::LoadObject(const ObjectSerializer& serializer)
    {
        super::LoadObject(serializer);
    }
#pragma endregion //GeneratedCodeSource

    GameSystem* GameSystemInitData::InstanciateGameSystem() const
    {
        return nullptr;
    }
}
