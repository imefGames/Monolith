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

        Vec2f GetPosition() const { return m_Position; }
        void SetPosition(Vec2f newValue) { m_Position = newValue; }

        virtual Entity* InstantiateEntity() const;

    private:
        using super = Object;

        Vec2f m_Position;
    };
#pragma endregion //GeneratedCodeHeader
}
