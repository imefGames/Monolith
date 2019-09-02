#pragma once

#include <engine/model/object.h>

namespace Monolith
{
    class EntityInitData;
    class World;

    using EntityDataArray = std::vector<EntityInitData*>;
    using EntityDataOutputArray = const std::vector<EntityInitData*>&;

#pragma region GeneratedCodeHeader
    class WorldInitData : public Object
    {
    public:
        WorldInitData();
        ~WorldInitData();

        void LoadObject(const ObjectSerializer& serializer) override;


        World* InstantiateWorld() const;
        EntityDataOutputArray GetEntities() const;

    private:
        using super = Object;

        EntityDataArray m_Entities;
    };
#pragma endregion //GeneratedCodeHeader
}
