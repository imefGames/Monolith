#pragma once

#include <vector>

namespace Monolith
{
    class Entity;
    class RenderingContext;
    class WorldInitData;

    class World
    {
    public:
        World(const WorldInitData& worldInitData);

        void Init();
        void Shutdown();
        void Update(f32 deltaTime);
        void Render(RenderingContext& renderingContext);

    private:
        std::vector<Entity*> m_Entities;
    };
}