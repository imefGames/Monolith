#pragma once

#include <core/signal.hpp>
#include <core/singleton.h>
#include <engine/model/gamesystem.h>

namespace Monolith
{
    class InputEvents;

    enum class EMouseButton
    {
        Left,
        Middle,
        Right
    };

    class InputProcessor : public GameSystem, public Singleton<InputProcessor>
    {
    public:
        void ProcessInputEvents(const InputEvents& inputEvents);

        inline Signal<EMouseButton, u32, u32>& GetMouseClickedSignal() { return m_MouseClickedSignal; }

    protected:
        void OnInit() override;
        void OnShutdown() override;

    private:
        Signal<EMouseButton, u32, u32> m_MouseClickedSignal;
    };

    namespace InputHelper
    {
        void ProcessInputEvents(const InputEvents& inputEvents);
    }
}