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
}