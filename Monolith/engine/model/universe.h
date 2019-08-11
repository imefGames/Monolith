#pragma once

#include <vector>

namespace Monolith
{
    class GameSystem;
    class World;

    class Universe
    {
    public:
        void Init();
        void Shutdown();
        void Update(f32 deltaTime);

    private:
        std::vector<GameSystem*> m_Systems;
        std::vector<World*> m_Worlds;
    };
}