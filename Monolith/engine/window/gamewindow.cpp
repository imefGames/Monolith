#include <precomp.h>
#include <engine/window/gamewindow.h>

#include <engine/input/inputevents.h>
#include <engine/rendering/renderingcontext.h>

#include <Windows.h>

namespace Monolith
{
    namespace GameWindowHelperInternal
    {
        void OnKeyEvent(const KEY_EVENT_RECORD& keyEvent, InputEvents& inputEvents);
        void OnMouseEvent(const MOUSE_EVENT_RECORD& mouseEvent, InputEvents& inputEvents);
    }

    GameWindow::GameWindow()
    {
    }

    GameWindow::~GameWindow()
    {
    }

    void GameWindow::Init(const GameWindowData& gameWindowData)
    {
        HANDLE stdInHandle{ GetStdHandle(STD_INPUT_HANDLE) };
        SetConsoleMode(stdInHandle, ENABLE_EXTENDED_FLAGS);
        SetConsoleMode(stdInHandle, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
    }

    void GameWindow::Shutdown()
    {
    }

    void GameWindow::PollInputEvents(InputEvents& inputEvents)
    {
        inputEvents.Reset();

        u32 readEvents;
        INPUT_RECORD irInBuf[128];
        ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), irInBuf, 128, &readEvents);
        for (u32 i = 0; i < readEvents; i++)
        {
            switch (irInBuf[i].EventType)
            {
                case KEY_EVENT:
                {
                    GameWindowHelperInternal::OnKeyEvent(irInBuf[i].Event.KeyEvent, inputEvents);
                    break;
                }

                case MOUSE_EVENT:
                {
                    GameWindowHelperInternal::OnMouseEvent(irInBuf[i].Event.MouseEvent, inputEvents);
                    break;
                }
            }
        }
    }

    void GameWindow::SetupRenderingContext(RenderingContext& renderingContext)
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        u32 columns, rows;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        columns = csbi.srWindow.Right - csbi.srWindow.Left;
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top;

        renderingContext.SetWindowSize(columns, rows);
    }

    namespace GameWindowHelperInternal
    {
        void OnKeyEvent(const KEY_EVENT_RECORD& keyEvent, InputEvents& inputEvents)
        {
        }

        void OnMouseEvent(const MOUSE_EVENT_RECORD& mouseEvent, InputEvents& inputEvents)
        {
            switch (mouseEvent.dwEventFlags)
            {
                case 0:
                {
                    if (mouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
                    {
                        inputEvents.SetMouseEvent(EMouseInputEvent::LClick);
                        inputEvents.SetMousePosition(Vec2{ static_cast<f32>(mouseEvent.dwMousePosition.X), static_cast<f32>(mouseEvent.dwMousePosition.Y) });
                    }
                    else if (mouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
                    {
                        inputEvents.SetMouseEvent(EMouseInputEvent::RClick);
                        inputEvents.SetMousePosition(Vec2{ static_cast<f32>(mouseEvent.dwMousePosition.X), static_cast<f32>(mouseEvent.dwMousePosition.Y) });
                    }
                    else
                    {
                        // Unhandled
                    }
                    break;
                }

                case MOUSE_MOVED:
                {
                    inputEvents.SetMouseEvent(EMouseInputEvent::Move);
                    inputEvents.SetMousePosition(Vec2{ static_cast<f32>(mouseEvent.dwMousePosition.X), static_cast<f32>(mouseEvent.dwMousePosition.Y) });
                    break;
                }
            }
        }
    }
}