#include <precomp.h>
#include <engine/model/data/entityinitdata.h>

#include <core/serialization/objectserializer.h>
#include <engine/model/entity.h>

namespace Monolith
{
#pragma region GeneratedCodeSource
    EntityInitData::EntityInitData()
        : super{}
    {
    }

    EntityInitData::~EntityInitData()
    {
    }

    void EntityInitData::LoadObject(const ObjectSerializer& serializer)
    {
        super::LoadObject(serializer);
    }
#pragma endregion //GeneratedCodeSource

    Entity* EntityInitData::InstantiateEntity() const
    {
        return new Entity{ *this };
    }
}
