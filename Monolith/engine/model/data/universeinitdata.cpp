#include <precomp.h>
#include <engine/model/data/universeinitdata.h>

#include <core/serialization/objectserializer.h>
#include <engine/model/data/gamesysteminitdata.h>

namespace Monolith
{
#pragma region GeneratedCodeSource
    UniverseInitData::UniverseInitData()
        : super{}
        , m_GameSystems{  }
        , m_StartupWorld{  }
    {
    }

    UniverseInitData::~UniverseInitData()
    {
        ObjectHelper::Delete(m_GameSystems);
    }

    void UniverseInitData::LoadObject(const ObjectSerializer& serializer)
    {
        super::LoadObject(serializer);
        ObjectSerializationHelper::LoadObject(serializer["GameSystems"], m_GameSystems);
        ObjectSerializationHelper::LoadObject(serializer["StartupWorld"], m_StartupWorld);
    }
#pragma endregion //GeneratedCodeSource

    void UniverseInitData::InstantiateGameSystems(GameSystemOutputArray gameSystems) const
    {
        gameSystems.reserve(m_GameSystems.size());
        for (const GameSystemInitData* initData : m_GameSystems)
        {
            gameSystems.push_back(initData->InstantiateGameSystem());
        }
    }
}
