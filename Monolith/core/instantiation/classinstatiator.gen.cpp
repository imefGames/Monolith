// DO NOT TOUCH THIS FILE.
// IT CONTAINS ONLY GENERATED CODE.

#include <precomp.h>
#include <core/instantiation/classinstantiator.h>

#include <engine/data/universeinitdata.h>

namespace Monolith
{
    namespace ClassInstantiatorInternal
    {
        template <class T>
        void* InstantiateClass()
        {
            return new T{};
        }
    }

    void ClassInstatiator::InitInstantiatorMap()
    {
        m_ClassInstantiators[0] = ClassInstantiatorInternal::InstantiateClass<UniverseInitData>;
    }

    void ClassInstatiator::ShutdownInstantiatorMap()
    {
        m_ClassInstantiators.clear();
    }
}