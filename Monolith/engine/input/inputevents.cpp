#include <precomp.h>
#include <engine/input/inputevents.h>

namespace Monolith
{
    void InputEvents::Reset()
    {
        m_MouseEvent = EMouseInputEvent::None;
        m_MousePosition.GetX() = 0;
        m_MousePosition.GetY() = 0;
    }
}