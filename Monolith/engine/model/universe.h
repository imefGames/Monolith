#pragma once

#include <vector>

namespace Monolith
{
    class GameSystem;
    class RenderingContext;
    class World;

    class Universe
    {
    public:
        void Init();
        void Shutdown();
        void Update(f32 deltaTime);
        void Render(RenderingContext& renderingContext);

    private:
        std::vector<GameSystem*> m_Systems;
        std::vector<World*> m_Worlds;
    };
}