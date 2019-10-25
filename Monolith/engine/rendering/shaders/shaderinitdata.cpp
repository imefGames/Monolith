#include <precomp.h>
#include <engine/rendering/shaders/shaderinitdata.h>

#include <core/serialization/objectserializer.h>

namespace Monolith
{
#pragma region GeneratedCodeSource
    ShaderInitData::ShaderInitData()
        : super{}
    {
    }

    ShaderInitData::~ShaderInitData()
    {
    }

    void ShaderInitData::LoadObject(const ObjectSerializer& serializer)
    {
        super::LoadObject(serializer);
    }
#pragma endregion //GeneratedCodeSource

    Shader* ShaderInitData::InstantiateShader() const
    {
        return nullptr;
    }
}
