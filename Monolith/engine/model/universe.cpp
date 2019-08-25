#include <precomp.h>
#include <engine/model/universe.h>

#include <engine/model/gamesystem.h>
#include <engine/model/world.h>
#include <engine/model/data/universeinitdata.h>

namespace Monolith
{
    void Universe::Init(const UniverseInitData& universeInitData)
    {
        universeInitData.InstanciateGameSystems(m_Systems);
        for (GameSystem* currentSystem : m_Systems)
        {
            currentSystem->Init();
        }
    }

    void Universe::Shutdown()
    {
        for (GameSystem* currentSystem : m_Systems)
        {
            currentSystem->Shutdown();
            delete currentSystem;
        }
        m_Systems.clear();
    }

    void Universe::Update(f32 deltaTime)
    {
        for (GameSystem* currentSystem : m_Systems)
        {
            currentSystem->Update(deltaTime);
        }
        for (World* currentWorld : m_Worlds)
        {
            currentWorld->Update(deltaTime);
        }
    }

    void Universe::Render(RenderingContext& renderingContext)
    {
        for (GameSystem* currentSystem : m_Systems)
        {
            currentSystem->Render(renderingContext);
        }
        for (World* currentWorld : m_Worlds)
        {
            currentWorld->Render(renderingContext);
        }
    }
}