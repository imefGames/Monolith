#pragma once

#include <core/singleton.h>
#include <map>
#include <functional>

namespace Monolith
{
    class ClassInstatiator : public Singleton<ClassInstatiator>
    {
    public:
        void Init();
        void Shutdown();

        static void* Instantiate(u64 classID);

        template <class T>
        static T* Instantiate(u64 classID)
        {
            return reinterpret_cast<T*>(Instantiate(classID));
        }

    private:
        void InitInstantiatorMap();
        void ShutdownInstantiatorMap();

        std::map<u64, std::function<void*()>> m_ClassInstantiators;
    };
}