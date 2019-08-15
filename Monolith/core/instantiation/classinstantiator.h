#pragma once

#include <core/singleton.h>

namespace Monolith
{
    class ClassInstatiator : public Singleton<ClassInstatiator>
    {
    public:
        void Init();
        void Shutdown();

        template <class T>
        static T* Instantiate(u64 classID)
        {
            Report::Assert(false, "[ClassInstatiator::Instantiate] Not yet implemented");
        }
    };
}