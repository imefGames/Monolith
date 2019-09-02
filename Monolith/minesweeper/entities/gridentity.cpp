#include <precomp.h>
#include <minesweeper/entities/gridentity.h>

#include <core/serialization/objectserializer.h>

namespace Monolith
{
#pragma region GeneratedCodeSource
    GridEntityInitData::GridEntityInitData()
        : super{}
    {
    }

    GridEntityInitData::~GridEntityInitData()
    {
    }

    void GridEntityInitData::LoadObject(const ObjectSerializer& serializer)
    {
        super::LoadObject(serializer);
    }
#pragma endregion //GeneratedCodeSource

    Entity* GridEntityInitData::InstanciateEntity() const
    {
        return new GridEntity{ *this };
    }



    GridEntity::GridEntity(const GridEntityInitData& gridEntityInitData)
        : Entity{ gridEntityInitData }
    {
    }
}
