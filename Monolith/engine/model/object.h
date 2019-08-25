#pragma once

#include <vector>

namespace Monolith
{
    class ObjectSerializer;

    class Object
    {
    public:
        Object() = default;
        virtual ~Object() = default;

        virtual void LoadObject(const ObjectSerializer& serializer);
    };

    namespace ObjectHelper
    {
        template <class T>
        void Delete(T* object)
        {
            delete object;
        }

        template <class T>
        void Delete(std::vector<T*>& objectArray)
        {
            for (T* subObject : objectArray)
            {
                ObjectHelper::Delete(subObject);
            }
            objectArray.clear();
        }
    }

    namespace ObjectSerializationHelper
    {
        void LoadObject(const ObjectSerializer& serializer, Object& object);
    }
}