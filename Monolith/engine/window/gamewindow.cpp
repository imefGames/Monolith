#include <precomp.h>
#include <engine/window/gamewindow.h>

#include <engine/input/inputevents.h>
#include <engine/rendering/renderingcontext.h>
#include <engine/window/gamewindowdata.h>

namespace Monolith
{
    namespace GameWindowHelperInternal
    {
        InputEvents s_InputEvents;

        LRESULT CALLBACK HandleWindowEvents(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);
    }

    GameWindow::GameWindow()
        : m_InstanceHandle{ nullptr }
        , m_WindowHandle{ nullptr }
        , m_ApplicationName{ "Monolith" }
    {
    }

    GameWindow::~GameWindow()
    {
    }

    void GameWindow::Init(GameWindowData& gameWindowData)
    {
        m_InstanceHandle = GetModuleHandle(NULL);

        WNDCLASSEX wc;
        wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wc.lpfnWndProc = GameWindowHelperInternal::HandleWindowEvents;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = m_InstanceHandle;
        wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
        wc.hIconSm = wc.hIcon;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
        wc.lpszMenuName = NULL;
        wc.lpszClassName = m_ApplicationName;
        wc.cbSize = sizeof(WNDCLASSEX);
        RegisterClassEx(&wc);

        s32 screenWidth = 800;
        s32 screenHeight = 600;
        s32 posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
        s32 posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
        gameWindowData.SetScreenWidth(screenWidth);
        gameWindowData.SetScreenHeight(screenHeight);

        m_WindowHandle = CreateWindow(m_ApplicationName, m_ApplicationName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, screenWidth, screenHeight, NULL, NULL, m_InstanceHandle, NULL);
        gameWindowData.SetWindowHandle(m_WindowHandle);

        ShowWindow(m_WindowHandle, SW_SHOW);
        SetForegroundWindow(m_WindowHandle);
        SetFocus(m_WindowHandle);
    }

    void GameWindow::Shutdown()
    {
        DestroyWindow(m_WindowHandle);
        m_WindowHandle = nullptr;
        UnregisterClass(m_ApplicationName, m_InstanceHandle);
        m_InstanceHandle = nullptr;
    }

    void GameWindow::PollInputEvents(InputEvents& inputEvents)
    {
        GameWindowHelperInternal::s_InputEvents.Reset();
        MSG message;
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        inputEvents = GameWindowHelperInternal::s_InputEvents;
    }

    void GameWindow::SetupRenderingContext(RenderingContext& renderingContext)
    {
        //TODO: get from window size.
        renderingContext.SetWindowSize(800, 600);
    }

    namespace GameWindowHelperInternal
    {
        LRESULT CALLBACK HandleWindowEvents(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
        {
            LRESULT returnValue{};
            switch (message)
            {
                case WM_KEYDOWN:
                {
                    //keyboardKeyCode = static_cast<u32>(wParam);
                    break;
                }

                case WM_KEYUP:
                {
                    //keyboardKeyCode = static_cast<u32>(wParam);
                    break;
                }

                case WM_LBUTTONDOWN:
                {
                    s_InputEvents.SetMouseEvent(EMouseInputEvent::LClick);
                    break;
                }

                case WM_RBUTTONDOWN:
                {
                    s_InputEvents.SetMouseEvent(EMouseInputEvent::RClick);
                    break;
                }

                case WM_MOUSEMOVE:
                {
                    POINTS mousePosition = MAKEPOINTS(lParam);
                    s_InputEvents.SetMouseEvent(EMouseInputEvent::Move);
                    s_InputEvents.SetMousePosition(Vec2f{ static_cast<f32>(mousePosition.x), static_cast<f32>(mousePosition.y) });
                    break;
                }

                case WM_DESTROY:
                {
                    PostQuitMessage(0);
                    s_InputEvents.SetPressedQuit(true);
                    break;
                }

                default:
                {
                    returnValue = DefWindowProc(windowHandle, message, wParam, lParam);
                    break;
                }
            }

            return returnValue;
        }
    }
}