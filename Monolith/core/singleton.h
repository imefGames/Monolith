#pragma once

namespace Monolith
{
    template <class T>
    class Singleton
    {
    public:
        void RegisterInstance(T* instance)
        {
            //TODO: assert
            ms_Instance = instance;
        }

        void UnregisterInstance(T* instance)
        {
            //TODO: assert
            ms_Instance = nullptr;
        }

        static T* Get() { return ms_Instance; }

    private:
        static T* ms_Instance;
    };

    template <class T>
    T* Singleton<T>::ms_Instance = nullptr;
}