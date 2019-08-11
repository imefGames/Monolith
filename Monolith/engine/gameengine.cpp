#include <precomp.h>
#include <engine/gameengine.h>

#include <engine/flow/floworchestrator.h>
#include <engine/input/inputevents.h>
#include <engine/input/inputprocessor.h>
#include <engine/rendering/gamerenderer.h>
#include <engine/rendering/renderingcontext.h>

#include <chrono>

namespace Monolith
{
    void GameEngine::Init(const GameWindowData& gameWindowData)
    {
        m_GameWindow.Init(gameWindowData);
        m_Universe.Init();
    }

    void GameEngine::Shutdown()
    {
        m_Universe.Shutdown();
        m_GameWindow.Shutdown();
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