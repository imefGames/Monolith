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

        inline Signal<EMouseButton, Vec2f>& GetMouseClickedSignal() { return m_MouseClickedSignal; }

    protected:
        void OnInit() override;
        void OnShutdown() override;

    private:
        Signal<EMouseButton, Vec2f> m_MouseClickedSignal;
    };

    namespace InputHelper
    {
        void ProcessInputEvents(const InputEvents& inputEvents);
    }
}