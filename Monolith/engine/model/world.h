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

    private:
        std::vector<Entity*> m_Entities;
    };
}