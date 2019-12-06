#pragma once

namespace Monolith
{
    class EntityInitData;
    class RenderingContext;

    class Entity
    {
    public:
        Entity(const EntityInitData& entityInitData);

        inline const Vec4f& GetPosition() const { return m_Position; }
        inline void SetPosition(const Vec4f& newValue) { m_Position = newValue; }

        virtual void Init();
        virtual void Shutdown();
        virtual void Update(f32 deltaTime);

    private:
        Vec4f m_Position;
    };
}