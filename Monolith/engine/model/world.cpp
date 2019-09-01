#include <precomp.h>
#include <engine/model/world.h>

#include <engine/model/entity.h>
#include <engine/model/data/entityinitdata.h>
#include <engine/model/data/worldinitdata.h>

namespace Monolith
{
    World::World(const WorldInitData& worldInitData)
    {
        const std::vector<EntityInitData*>& entityDataArray{ worldInitData.GetEntities() };
        m_Entities.reserve(entityDataArray.size());
        for (const EntityInitData* entityData : entityDataArray)
        {
            m_Entities.push_back(entityData->InstanciateEntity());
        }
    }

    void World::Init()
    {
        for (Entity* currentEntity : m_Entities)
        {
            currentEntity->Init();
        }
    }

    void World::Shutdown()
    {
        for (Entity* currentEntity : m_Entities)
        {
            currentEntity->Shutdown();
        }
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