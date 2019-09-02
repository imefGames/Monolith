#pragma once

#include <engine/model/entity.h>
#include <engine/model/data/entityinitdata.h>

namespace Monolith
{
#pragma region GeneratedCodeHeader
    class GridEntityInitData : public EntityInitData
    {
    public:
        GridEntityInitData();
        ~GridEntityInitData();

        void LoadObject(const ObjectSerializer& serializer) override;


        Entity* InstantiateEntity() const override;

    private:
        using super = EntityInitData;

    };
#pragma endregion //GeneratedCodeHeader

    class GridEntity : public Entity
    {
    public:
        GridEntity(const GridEntityInitData& gridEntityInitData);
    };
}
