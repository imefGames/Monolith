#include <precomp.h>
#include <engine/model/data/worldinitdata.h>

#include <core/serialization/objectserializer.h>
#include <engine/model/world.h>
#include <engine/model/data/entityinitdata.h>

namespace Monolith
{
#pragma region GeneratedCodeSource
    WorldInitData::WorldInitData()
        : super{}
        , m_Entities{  }
    {
    }

    WorldInitData::~WorldInitData()
    {
        ObjectHelper::Delete(m_Entities);
    }

    void WorldInitData::LoadObject(const ObjectSerializer& serializer)
    {
        super::LoadObject(serializer);
        ObjectSerializationHelper::LoadObject(serializer["Entities"], m_Entities);
    }
#pragma endregion //GeneratedCodeSource

    World* WorldInitData::InstantiateWorld() const
    {
        return new World{ *this };
    }

    EntityDataOutputArray WorldInitData::GetEntities() const
    {
        return m_Entities;
    }
}
