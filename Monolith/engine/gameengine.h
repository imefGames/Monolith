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
        void Init(const GameWindowData& gameWindowData);
        void Shutdown();
        void RunGameLoop();

    private:
        ClassInstatiator m_ClassInstatiator;
        GameWindow m_GameWindow;
        Universe m_Universe;
    };
}