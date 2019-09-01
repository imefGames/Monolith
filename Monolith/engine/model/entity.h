#pragma once

namespace Monolith
{
    class EntityInitData;
    class RenderingContext;

    class Entity
    {
    public:
        Entity(const EntityInitData& entityInitData);

        void Init();
        void Shutdown();
        void Update(f32 deltaTime);
        void Render(RenderingContext& renderingContext);
    };
}