#include <precomp.h>
#include <engine/input/inputevents.h>

namespace Monolith
{
    InputEvents::InputEvents()
    {
        Reset();
    }

    void InputEvents::Reset()
    {
        m_MouseEvent = EMouseInputEvent::None;
        m_MousePosition[0] = 0;
        m_MousePosition[1] = 0;
        m_PressedQuit = false;
    }
}