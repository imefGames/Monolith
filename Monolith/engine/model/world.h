#pragma once

#include <vector>

namespace Monolith
{
    class Entity;

    class World
    {
    public:
        void Init();
        void Shutdown();

    private:
        std::vector<Entity*> m_Entities;
    };
}