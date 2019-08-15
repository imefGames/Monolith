#pragma once

#include <core/instantiation/classinstantiator.h>
#include <core/serialization/json/jsonNode.h>

namespace Monolith
{
    class ObjectSerializer
    {
    public:
        ObjectSerializer(const JSonNode& node);

        ObjectSerializer operator[](u32 index) const;
        ObjectSerializer operator[](const char* subSerializerName) const;

        inline const JSonNode& GetNode() const { return m_Node; }

    private:
        const JSonNode& m_Node;
    };

    namespace ObjectSerializationHelper
    {
        template <class T>
        void LoadObject(const ObjectSerializer& serializer, T& object)
        {
            JSonHelper::LoadObject(serializer.GetNode(), object);
        }
        template <class T>
        void LoadObject(const ObjectSerializer& serializer, T*& object)
        {
            u64 classIdentifier;
            ObjectSerializationHelper::LoadObject(serializer["ClassID"], classIdentifier);
            object = ClassInstatiator::Instantiate(classIdentifier);
            if (object != nullptr)
            {
                ObjectSerializationHelper::LoadObject(serializer, *object);
            }
        }

        template <class T>
        void LoadObject(const ObjectSerializer& serializer, std::vector<T>& objectVector)
        {
            objectVector.reserve(serializer.GetNode().GetSubNodeCount());
            for (const JSonNode& subNode : serializer.GetNode())
            {
                ObjectSerializer subSerializer{ subNode };
                T newObject{};
                ObjectSerializationHelper::LoadObject(subSerializer, newObject);
                objectVector.push_back(newObject);
            }
        }
    }
}