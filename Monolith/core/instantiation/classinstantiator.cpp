#include <precomp.h>
#include <core/instantiation/classinstantiator.h>

namespace Monolith
{
    void ClassInstatiator::Init()
    {
        RegisterInstance(this);

        InitInstantiatorMap();
    }

    void ClassInstatiator::Shutdown()
    {
        ShutdownInstantiatorMap();

        UnregisterInstance(this);
    }

    void* ClassInstatiator::Instantiate(u64 classID)
    {
        void* createdClass{ nullptr };
        const std::map<u64, std::function<void* ()>>& classInstantiators{ ClassInstatiator::Get()->m_ClassInstantiators };
        auto foundInstantiator{ classInstantiators.find(classID) };
        if (foundInstantiator != classInstantiators.end())
        {
            createdClass = foundInstantiator->second();
        }
        else
        {
            Report::Error(false, "Failed to create class.");
        }

        return createdClass;
    }
}