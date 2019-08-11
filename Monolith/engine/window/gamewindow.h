#pragma once

namespace Monolith
{
    class GameWindowData;
    class InputEvents;
    class RenderingContext;

    class GameWindow
    {
    public:
        GameWindow();
        ~GameWindow();

        void Init(const GameWindowData& gameWindowData);
        void Shutdown();

        void PollInputEvents(InputEvents& inputEvents);
        void SetupRenderingContext(RenderingContext& renderingContext);
    };
}