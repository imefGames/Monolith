#pragma once

#include <core/instantiation/classinstantiator.h>
#include <engine/model/universe.h>
#include <engine/window/gamewindow.h>

namespace Monolith
{
    class GameWindowData;
    class Universe;

    class GameEngine
    {
    public:
        void Init(GameWindowData& gameWindowData);
        void Shutdown();
        void RunGameLoop();

    private:
        static const char* K_GAME_FILE_NAME;

        ClassInstatiator m_ClassInstatiator;
        GameWindow m_GameWindow;
        Universe m_Universe;
    };
}