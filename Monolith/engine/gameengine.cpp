#include <precomp.h>
#include <engine/gameengine.h>

#include <core/io/filereader.h>
#include <core/serialization/objectserializer.h>
#include <core/serialization/json/jsonparser.h>
#include <engine/data/universeinitdata.h>
#include <engine/flow/floworchestrator.h>
#include <engine/input/inputevents.h>
#include <engine/input/inputprocessor.h>
#include <engine/rendering/gamerenderer.h>
#include <engine/rendering/renderingcontext.h>

#include <chrono>

namespace Monolith
{
    const char* GameEngine::K_GAME_FILE_NAME = "gamedata.json";

    void GameEngine::Init(const GameWindowData& gameWindowData)
    {
        m_ClassInstatiator.Init();
        m_GameWindow.Init(gameWindowData);

        std::string gameData;
        FileReader gameDataReader{ K_GAME_FILE_NAME };
        gameDataReader.ReadFullFile(gameData);

        JSonParser parser{ gameData };
        ObjectSerializer universeDataSerializer{ parser.GetRootNode() };

        UniverseInitData universeInitData;
        ObjectSerializationHelper::LoadObject(universeDataSerializer, universeInitData);

        m_Universe.Init(universeInitData);
    }

    void GameEngine::Shutdown()
    {
        m_Universe.Shutdown();
        m_GameWindow.Shutdown();
        m_ClassInstatiator.Shutdown();
    }

    void GameEngine::RunGameLoop()
    {
        InputEvents inputEvents;
        RenderingContext renderingContext;

        f32 deltaTime{ 0.033f };
        auto previousTime = std::chrono::steady_clock::now();
        while (FlowHelper::IsGameRunning())
        {
            auto frameStart = std::chrono::steady_clock::now();

            m_GameWindow.PollInputEvents(inputEvents);
            m_GameWindow.SetupRenderingContext(renderingContext);

            RenderingHelper::StartFrame(renderingContext);
            InputHelper::ProcessInputEvents(inputEvents);
            m_Universe.Update(deltaTime);
            m_Universe.Render(renderingContext);
            RenderingHelper::EndFrame(renderingContext);

            auto frameEnd = std::chrono::steady_clock::now();
            std::chrono::duration<f32, std::milli> duration(std::chrono::duration_cast<std::chrono::duration<f32, std::milli>>(frameEnd - frameStart));
            deltaTime = duration.count() * 0.001f;
        }
    }
}