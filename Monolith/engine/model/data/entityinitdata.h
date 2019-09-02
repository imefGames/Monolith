#pragma once

#include <engine/model/object.h>

namespace Monolith
{
    class Entity;

#pragma region GeneratedCodeHeader
    class EntityInitData : public Object
    {
    public:
        EntityInitData();
        ~EntityInitData();

        void LoadObject(const ObjectSerializer& serializer) override;


        virtual Entity* InstanciateEntity() const;

    private:
        using super = Object;

    };
#pragma endregion //GeneratedCodeHeader
}
