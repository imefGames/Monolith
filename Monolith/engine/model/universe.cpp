#include <precomp.h>
#include <engine/model/universe.h>

#include <core/io/filereader.h>
#include <core/serialization/objectserializer.h>
#include <core/serialization/json/jsonparser.h>
#include <engine/model/gamesystem.h>
#include <engine/model/world.h>
#include <engine/model/data/universeinitdata.h>
#include <engine/model/data/worldinitdata.h>
#include <algorithm>

namespace Monolith
{
    Universe::Universe()
        : m_CurrentWorld{ nullptr }
    {
    }

    void Universe::Init(const UniverseInitData& universeInitData)
    {
        RegisterInstance(this);

        universeInitData.InstantiateGameSystems(m_Systems);
        for (GameSystem* currentSystem : m_Systems)
        {
            currentSystem->Init();
        }
    }

    void Universe::Shutdown()
    {
        if (m_CurrentWorld != nullptr)
        {
            m_CurrentWorld->Shutdown();
        }

        std::for_each(m_Systems.rbegin(), m_Systems.rend(), [](GameSystem* currentSystem)
        {
            currentSystem->Shutdown();
            delete currentSystem;
        });
        m_Systems.clear();

        UnregisterInstance(this);
    }

    void Universe::Update(f32 deltaTime)
    {
        for (GameSystem* currentSystem : m_Systems)
        {
            currentSystem->Update(deltaTime);
        }
        
        if (m_CurrentWorld != nullptr)
        {
            m_CurrentWorld->Update(deltaTime);
        }
    }

    void Universe::GoToWorld(const std::string& destinationWorld)
    {
        if (m_CurrentWorld != nullptr)
        {
            m_CurrentWorld->Shutdown();
            delete m_CurrentWorld;
        }

        m_CurrentWorld = LoadWorld(destinationWorld);

        if (m_CurrentWorld != nullptr)
        {
            m_CurrentWorld->Init();
        }
    }

    World* Universe::LoadWorld(const std::string& worldPath) const
    {
        std::string worldData;
        FileReader gameDataReader{ worldPath.c_str() };
        gameDataReader.ReadFullFile(worldData);

        JSonParser parser{ worldData };
        ObjectSerializer worldDataSerializer{ parser.GetRootNode() };

        WorldInitData worldInitData;
        ObjectSerializationHelper::LoadObject(worldDataSerializer, worldInitData);
        return worldInitData.InstantiateWorld();
    }
}