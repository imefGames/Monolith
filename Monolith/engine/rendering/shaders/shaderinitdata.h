#pragma once

#include <engine/model/object.h>

namespace Monolith
{
    class Shader;

#pragma region GeneratedCodeHeader
    class ShaderInitData : public Object
    {
    public:
        ShaderInitData();
        ~ShaderInitData();

        void LoadObject(const ObjectSerializer& serializer) override;


        Shader* InstantiateShader() const;

    private:
        using super = Object;

    };
#pragma endregion //GeneratedCodeHeader
}
