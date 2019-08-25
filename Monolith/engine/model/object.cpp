#include <precomp.h>
#include <engine/model/object.h>

namespace Monolith
{
    void Object::LoadObject(const ObjectSerializer& serializer)
    {
    }

    namespace ObjectSerializationHelper
    {
        void LoadObject(const ObjectSerializer& serializer, Object& object)
        {
            object.LoadObject(serializer);
        }
    }
}