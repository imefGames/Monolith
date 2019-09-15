#pragma once

#include <Windows.h>

namespace Monolith
{
    class GameWindowData
    {
    public:
        GameWindowData();

        HWND GetWindowHandle() const { return m_WindowHandle; }
        void SetWindowHandle(HWND windowHandle) { m_WindowHandle = windowHandle; }

        s32 GetScreenWidth() const { return m_ScreenWidth; }
        void SetScreenWidth(s32 screenWidth) { m_ScreenWidth = screenWidth; }

        s32 GetScreenHeight() const { return m_ScreenHeight; }
        void SetScreenHeight(s32 screenHeight) { m_ScreenHeight = screenHeight; }

    private:
        HWND m_WindowHandle;
        s32 m_ScreenWidth;
        s32 m_ScreenHeight;
    };
}