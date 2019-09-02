#include <precomp.h>
#include <engine/model/data/entityinitdata.h>

#include <core/serialization/objectserializer.h>
#include <engine/model/entity.h>

namespace Monolith
{
#pragma region GeneratedCodeSource
    EntityInitData::EntityInitData()
        : super{}
        , m_Position{  }
    {
    }

    EntityInitData::~EntityInitData()
    {
    }

    void EntityInitData::LoadObject(const ObjectSerializer& serializer)
    {
        super::LoadObject(serializer);
        ObjectSerializationHelper::LoadObject(serializer["Position"], m_Position);
    }
#pragma endregion //GeneratedCodeSource

    Entity* EntityInitData::InstantiateEntity() const
    {
        return new Entity{ *this };
    }
}
