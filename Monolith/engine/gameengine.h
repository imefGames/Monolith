#pragma once

#include <engine/model/universe.h>
#include <engine/window/gamewindow.h>

namespace Monolith
{
    class GameWindowData;
    class Universe;

    class GameEngine
    {
    public:
        void Init(const GameWindowData& gameWindowData);
        void Shutdown();
        void RunGameLoop();

    private:
        GameWindow m_GameWindow;
        Universe m_Universe;
    };
}