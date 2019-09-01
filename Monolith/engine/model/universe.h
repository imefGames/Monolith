#pragma once

#include <string>
#include <vector>

namespace Monolith
{
    class GameSystem;
    class RenderingContext;
    class UniverseInitData;
    class World;

    class Universe
    {
    public:
        void Init(const UniverseInitData& universeInitData);
        void Shutdown();
        void Update(f32 deltaTime);
        void Render(RenderingContext& renderingContext);

    private:
        World* LoadWorld(const std::string& worldPath) const;

        std::vector<GameSystem*> m_Systems;
        World* m_CurrentWorld;
    };
}