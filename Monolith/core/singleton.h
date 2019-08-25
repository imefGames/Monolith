#pragma once

namespace Monolith
{
    template <class T>
    class Singleton
    {
    public:
        void RegisterInstance(T* instance)
        {
            Report::Assert(ms_Instance == nullptr, "[Singleton] The singleton already has an instance.");
            ms_Instance = instance;
        }

        void UnregisterInstance(T* instance)
        {
            Report::Assert(ms_Instance == instance, "[Singleton] Trying to unregister the wrong instance.");
            ms_Instance = nullptr;
        }

        static T* Get() { return ms_Instance; }

    private:
        static T* ms_Instance;
    };

    template <class T>
    T* Singleton<T>::ms_Instance = nullptr;
}