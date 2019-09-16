#pragma once

namespace Monolith
{
    class EntityInitData;
    class RenderingContext;

    class Entity
    {
    public:
        Entity(const EntityInitData& entityInitData);

        inline Vec2f GetPosition() const { return m_Position; }
        inline void SetPosition(Vec2f newValue) { m_Position = newValue; }

        virtual void Init();
        virtual void Shutdown();
        virtual void Update(f32 deltaTime);
        virtual void Render(RenderingContext& renderingContext);

    private:
        Vec2f m_Position;
    };
}