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
        UnregisterInstance(this);
    }

    void InputProcessor::ProcessInputEvents(const InputEvents& inputEvents)
    {
        //TODO
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