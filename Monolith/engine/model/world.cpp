#include <precomp.h>
#include <engine/model/world.h>

#include <engine/model/entity.h>

namespace Monolith
{
    void World::Init()
    {
    }

    void World::Shutdown()
    {
    }

    void World::Update(f32 deltaTime)
    {
        for (Entity* currentEntity : m_Entities)
        {
            currentEntity->Update(deltaTime);
        }
    }

    void World::Render(RenderingContext& renderingContext)
    {
        for (Entity* currentEntity : m_Entities)
        {
            currentEntity->Render(renderingContext);
        }
    }
}