#pragma once

#include <Windows.h>

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

        void Init(GameWindowData& gameWindowData);
        void Shutdown();

        void PollInputEvents(InputEvents& inputEvents);
        void SetupRenderingContext(RenderingContext& renderingContext);

    public:
        HINSTANCE m_InstanceHandle;
        HWND m_WindowHandle;
        LPCSTR m_ApplicationName;
    };
}