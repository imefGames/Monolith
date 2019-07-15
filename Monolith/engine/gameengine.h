#pragma once

#include <engine/window/gamewindow.h>

namespace Monolith
{
    class GameWindowData;

    class GameEngine
    {
    public:
        void Init(const GameWindowData& gameWindowData);
        void Shutdown();
        void RunGameLoop();

    private:
        GameWindow m_GameWindow;
    };
}