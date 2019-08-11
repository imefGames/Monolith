#pragma once

#include <core/singleton.h>
#include <engine/model/gamesystem.h>

namespace Monolith
{
    class InputEvents;

    class InputProcessor : public GameSystem, public Singleton<InputProcessor>
    {
    public:
        void ProcessInputEvents(const InputEvents& inputEvents);

    protected:
        void OnInit() override;
        void OnShutdown() override;
    };

    namespace InputHelper
    {
        void ProcessInputEvents(const InputEvents& inputEvents);
    }
}