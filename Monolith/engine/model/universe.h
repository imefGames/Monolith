#pragma once

#include <core/singleton.h>
#include <string>
#include <vector>

namespace Monolith
{
    class GameSystem;
    class RenderingContext;
    class UniverseInitData;
    class World;

    class Universe : public Singleton<Universe>
    {
    public:
        Universe();

        void Init(const UniverseInitData& universeInitData);
        void Shutdown();
        void Update(f32 deltaTime);

        void GoToWorld(const std::string& destinationWorld);

    private:
        World* LoadWorld(const std::string& worldPath) const;

        std::vector<GameSystem*> m_Systems;
        World* m_CurrentWorld;
    };
}