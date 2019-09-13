#include <precomp.h>

#include <engine/gameengine.h>
#include <engine/window/gamewindowdata.h>
#include <Windows.h>

int WINAPI WinMain(HINSTANCE instanceHandle, HINSTANCE prevInstanceHandle, PSTR cmdline, int cmdshow)
{
    Monolith::GameWindowData windowData{};

    Monolith::GameEngine engine{};
    engine.Init(windowData);
    engine.RunGameLoop();
    engine.Shutdown();

    return 0;
}