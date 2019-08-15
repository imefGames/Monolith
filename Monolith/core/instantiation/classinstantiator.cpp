#include <precomp.h>
#include <core/instantiation/classinstantiator.h>

namespace Monolith
{
    void ClassInstatiator::Init()
    {
        RegisterInstance(this);
    }

    void ClassInstatiator::Shutdown()
    {
        UnregisterInstance(this);
    }
}