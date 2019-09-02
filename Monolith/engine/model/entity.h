#pragma once

namespace Monolith
{
    class EntityInitData;
    class RenderingContext;

    class Entity
    {
    public:
        Entity(const EntityInitData& entityInitData);

        virtual void Init();
        virtual void Shutdown();
        virtual void Update(f32 deltaTime);
        virtual void Render(RenderingContext& renderingContext);
    };
}