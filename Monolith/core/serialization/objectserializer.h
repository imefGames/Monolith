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
        void LoadObject(const ObjectSerializer& serializer, T*& object)
        {
            u32 classIdentifier;
            ObjectSerializationHelper::LoadObject(serializer["ClassID"], classIdentifier);
            object = ClassInstatiator::Instantiate<T>(classIdentifier);
            if (object != nullptr)
            {
                ObjectSerializationHelper::LoadObject(serializer, *object);
            }
        }

        template <class T>
        void LoadObject(const ObjectSerializer& serializer, std::vector<T>& objectVector)
        {
            objectVector.reserve(serializer.GetNode().GetSubNodeCount());
            for (u32 i = 0; i < serializer.GetNode().GetSubNodeCount(); ++i)
            {
                ObjectSerializer subSerializer{ serializer.GetNode()[i] };
                objectVector.push_back(T{});
                ObjectSerializationHelper::LoadObject(subSerializer, objectVector.back());
            }
        }

        void LoadObject(const ObjectSerializer& serializer, s32& loadedS32);
        void LoadObject(const ObjectSerializer& serializer, u32& loadedU32);
        void LoadObject(const ObjectSerializer& serializer, f32& loadedF32);
        void LoadObject(const ObjectSerializer& serializer, Vec2& loadedVec2);
        void LoadObject(const ObjectSerializer& serializer, std::string& loadedString);
    }
}