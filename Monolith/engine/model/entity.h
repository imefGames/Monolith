#pragma once

namespace Monolith
{
    class RenderingContext;

    class Entity
    {
    public:
        void Init();
        void Shutdown();
        void Update(f32 deltaTime);
        void Render(RenderingContext& renderingContext);
    };
}