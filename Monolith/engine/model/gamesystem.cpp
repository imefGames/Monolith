#include <precomp.h>
#include <engine/model/gamesystem.h>

namespace Monolith
{
    void GameSystem::Init()
    {
        OnInit();
    }

    void GameSystem::Shutdown()
    {
        OnShutdown();
    }

    void GameSystem::Update(f32 deltaTime)
    {
        OnUpdate(deltaTime);
    }

    void GameSystem::Render(RenderingContext& renderingContext)
    {
        OnRender(renderingContext);
    }
}