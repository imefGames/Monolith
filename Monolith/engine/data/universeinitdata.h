#pragma once

namespace Monolith
{
    class ObjectSerializer;

    class UniverseInitData
    {
    };

    namespace ObjectSerializationHelper
    {
        void LoadObject(const ObjectSerializer& serializer, UniverseInitData& universeInitData);
    }
}