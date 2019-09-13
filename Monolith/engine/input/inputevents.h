#pragma once

enum class EMouseInputEvent
{
    None,
    Move,
    LClick,
    RClick
};

namespace Monolith
{
    class InputEvents
    {
    public:
        InputEvents();

        inline EMouseInputEvent GetMouseEvent() const { return m_MouseEvent; }
        inline void SetMouseEvent(EMouseInputEvent mouseInputEvent) { m_MouseEvent = mouseInputEvent; }
        inline const Vec2& GetMousePosition() const { return m_MousePosition; }
        inline void SetMousePosition(const Vec2& position) { m_MousePosition = position; }
        inline bool GetPressedQuit() const { return m_PressedQuit; }
        inline void SetPressedQuit(bool pressedQuit) { m_PressedQuit = pressedQuit; }

        void Reset();

    private:
        EMouseInputEvent m_MouseEvent;
        Vec2 m_MousePosition;
        bool m_PressedQuit;
    };
}