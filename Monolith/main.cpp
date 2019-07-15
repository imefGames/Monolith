#include <precomp.h>

#include <engine/gameengine.h>
#include <engine/window/gamewindowdata.h>

Monolith::s32 main()
{
    Monolith::GameWindowData windowData{};

    Monolith::GameEngine engine{};
    engine.Init(windowData);
    engine.RunGameLoop();
    engine.Shutdown();

    return 0;
}