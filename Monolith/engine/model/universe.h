#pragma once

#include <vector>

namespace Monolith
{
    class World;

    class Universe
    {
    public:
        void Init();
        void Shutdown();

    private:
        std::vector<World*> m_Worlds;
    };
}