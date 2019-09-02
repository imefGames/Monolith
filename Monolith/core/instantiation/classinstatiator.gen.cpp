// DO NOT TOUCH THIS FILE.
// IT CONTAINS ONLY GENERATED CODE.

#include <precomp.h>
#include <core/instantiation/classinstantiator.h>

#include <engine/flow/flowaction.h>
#include <engine/flow/flowcondition.h>
#include <engine/flow/floworchestratorinitdata.h>
#include <engine/flow/flowstate.h>
#include <engine/flow/flowtransition.h>
#include <engine/flow/actions/gotoworldflowaction.h>
#include <engine/input/inputprocessorinitdata.h>
#include <engine/model/data/entityinitdata.h>
#include <engine/model/data/gamesysteminitdata.h>
#include <engine/model/data/universeinitdata.h>
#include <engine/model/data/worldinitdata.h>
#include <engine/rendering/gamerendererinitdata.h>
#include <minesweeper/entities/gamestatebuttonentity.h>
#include <minesweeper/entities/gridentity.h>
#include <minesweeper/flow/gamestateflowcondition.h>
#include <minesweeper/systems/minesweepergamesystem.h>

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
        m_ClassInstantiators[2698093165] = ClassInstantiatorInternal::InstantiateClass<FlowActionData>;
        m_ClassInstantiators[2165613468] = ClassInstantiatorInternal::InstantiateClass<FlowConditionData>;
        m_ClassInstantiators[2898161564] = ClassInstantiatorInternal::InstantiateClass<FlowOrchestratorInitData>;
        m_ClassInstantiators[1260209217] = ClassInstantiatorInternal::InstantiateClass<FlowStateData>;
        m_ClassInstantiators[1645509430] = ClassInstantiatorInternal::InstantiateClass<FlowTransitionData>;
        m_ClassInstantiators[4093385860] = ClassInstantiatorInternal::InstantiateClass<GoToWorldFlowActionData>;
        m_ClassInstantiators[4168157516] = ClassInstantiatorInternal::InstantiateClass<InputProcessorInitData>;
        m_ClassInstantiators[2914255181] = ClassInstantiatorInternal::InstantiateClass<EntityInitData>;
        m_ClassInstantiators[2331519880] = ClassInstantiatorInternal::InstantiateClass<GameSystemInitData>;
        m_ClassInstantiators[909029241] = ClassInstantiatorInternal::InstantiateClass<UniverseInitData>;
        m_ClassInstantiators[2938514964] = ClassInstantiatorInternal::InstantiateClass<WorldInitData>;
        m_ClassInstantiators[1580459700] = ClassInstantiatorInternal::InstantiateClass<GameRendererInitData>;
        m_ClassInstantiators[1442012994] = ClassInstantiatorInternal::InstantiateClass<GameStateButtonEntityInitData>;
        m_ClassInstantiators[3695653038] = ClassInstantiatorInternal::InstantiateClass<GridEntityInitData>;
        m_ClassInstantiators[2476956763] = ClassInstantiatorInternal::InstantiateClass<GameStateFlowConditionData>;
        m_ClassInstantiators[4271893737] = ClassInstantiatorInternal::InstantiateClass<MinesweeperGameSystemInitData>;
    }

    void ClassInstatiator::ShutdownInstantiatorMap()
    {
        m_ClassInstantiators.clear();
    }
}