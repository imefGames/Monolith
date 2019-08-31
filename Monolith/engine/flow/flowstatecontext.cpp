#include <precomp.h>
#include <engine/flow/flowstatecontext.h>

namespace Monolith
{
    FlowStateContext::FlowStateContext()
        : m_NextStateID{ u32Max }
    {
    }
}
