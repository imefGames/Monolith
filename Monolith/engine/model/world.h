#pragma once

#include <vector>

namespace Monolith
{
    class Entity;
    class RenderingContext;

    class World
    {
    public:
        void Init();
        void Shutdown();
        void Update(f32 deltaTime);
        void Render(RenderingContext& renderingContext);

    private:
        std::vector<Entity*> m_Entities;
    };
}