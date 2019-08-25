// DO NOT TOUCH THIS FILE.
// IT CONTAINS ONLY GENERATED CODE.

#include <precomp.h>
#include <core/instantiation/classinstantiator.h>

#include <engine/flow/floworchestratorinitdata.h>
#include <engine/input/inputprocessorinitdata.h>
#include <engine/model/data/gamesysteminitdata.h>
#include <engine/model/data/universeinitdata.h>
#include <engine/rendering/gamerendererinitdata.h>

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
        m_ClassInstantiators[2898161564] = ClassInstantiatorInternal::InstantiateClass<FlowOrchestratorInitData>;
        m_ClassInstantiators[4168157516] = ClassInstantiatorInternal::InstantiateClass<InputProcessorInitData>;
        m_ClassInstantiators[2331519880] = ClassInstantiatorInternal::InstantiateClass<GameSystemInitData>;
        m_ClassInstantiators[909029241] = ClassInstantiatorInternal::InstantiateClass<UniverseInitData>;
        m_ClassInstantiators[1580459700] = ClassInstantiatorInternal::InstantiateClass<GameRendererInitData>;
    }

    void ClassInstatiator::ShutdownInstantiatorMap()
    {
        m_ClassInstantiators.clear();
    }
}