#include <precomp.h>
#include <core/serialization/objectserializer.h>

namespace Monolith
{
    ObjectSerializer::ObjectSerializer(const JSonNode& node)
        : m_Node{ node }
    {
    }

    ObjectSerializer ObjectSerializer::operator[](u32 index) const
    {
        return ObjectSerializer{ m_Node[index] };
    }

    ObjectSerializer ObjectSerializer::operator[](const char* subSerializerName) const
    {
        return ObjectSerializer{ m_Node[subSerializerName] };
    }

    namespace ObjectSerializationHelper
    {
        void LoadObject(const ObjectSerializer& serializer, s32& loadedS32)
        {
            JSonHelper::LoadObject(serializer.GetNode(), loadedS32);
        }

        void LoadObject(const ObjectSerializer& serializer, u32& loadedU32)
        {
            JSonHelper::LoadObject(serializer.GetNode(), loadedU32);
        }

        void LoadObject(const ObjectSerializer& serializer, f32& loadedF32)
        {
            JSonHelper::LoadObject(serializer.GetNode(), loadedF32);
        }

        void LoadObject(const ObjectSerializer& serializer, Vec2& loadedVec2)
        {
            LoadObject(serializer["X"], loadedVec2.GetX());
            LoadObject(serializer["Y"], loadedVec2.GetY());
        }

        void LoadObject(const ObjectSerializer& serializer, std::string& loadedString)
        {
            JSonHelper::LoadObject(serializer.GetNode(), loadedString);
        }
    }
}