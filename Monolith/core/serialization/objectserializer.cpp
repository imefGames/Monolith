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
        void LoadObject(const ObjectSerializer& serializer, bool& loadedBool)
        {
            JSonHelper::LoadObject(serializer.GetNode(), loadedBool);
        }

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

        void LoadObject(const ObjectSerializer& serializer, Vec2f& loadedVec2f)
        {
            LoadObject(serializer["X"], loadedVec2f[0]);
            LoadObject(serializer["Y"], loadedVec2f[1]);
        }

        void LoadObject(const ObjectSerializer& serializer, Vec3f& loadedVec3f)
        {
            LoadObject(serializer["X"], loadedVec3f[0]);
            LoadObject(serializer["Y"], loadedVec3f[1]);
            LoadObject(serializer["Z"], loadedVec3f[2]);
        }

        void LoadObject(const ObjectSerializer& serializer, Vec4f& loadedVec4f)
        {
            LoadObject(serializer["X"], loadedVec4f[0]);
            LoadObject(serializer["Y"], loadedVec4f[1]);
            LoadObject(serializer["Z"], loadedVec4f[2]);
            LoadObject(serializer["W"], loadedVec4f[3]);
        }

        void LoadObject(const ObjectSerializer& serializer, std::string& loadedString)
        {
            JSonHelper::LoadObject(serializer.GetNode(), loadedString);
        }
    }
}