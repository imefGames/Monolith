#include <precomp.h>
#include <engine/model/universe.h>

#include <engine/flow/floworchestrator.h>
#include <engine/model/gamesystem.h>
#include <engine/model/world.h>

namespace Monolith
{
    void Universe::Init()
    {
        //TODO: add systems from data
        m_Systems.push_back(new FlowOrchestrator());

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
    }
}