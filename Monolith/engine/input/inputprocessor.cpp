#include <precomp.h>
#include <engine/input/inputprocessor.h>

#include <engine/input/inputevents.h>

namespace Monolith
{
    void InputProcessor::OnInit()
    {
        RegisterInstance(this);
    }

    void InputProcessor::OnShutdown()
    {
        m_MouseClickedSignal.DisconnectAll();
        UnregisterInstance(this);
    }

    void InputProcessor::ProcessInputEvents(const InputEvents& inputEvents)
    {
        EMouseInputEvent mouseEvent{ inputEvents.GetMouseEvent() };
        if (mouseEvent == EMouseInputEvent::LClick)
        {
            m_MouseClickedSignal.Emit(EMouseButton::Left, inputEvents.GetMousePosition());
        }
        else if (mouseEvent == EMouseInputEvent::RClick)
        {
            m_MouseClickedSignal.Emit(EMouseButton::Right, inputEvents.GetMousePosition());
        }
    }

    namespace InputHelper
    {
        void ProcessInputEvents(const InputEvents& inputEvents)
        {
            InputProcessor* inputProcessor{ InputProcessor::Get() };
            if (inputProcessor != nullptr)
            {
                inputProcessor->ProcessInputEvents(inputEvents);
            }
        }
    }
}