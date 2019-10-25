#pragma once

#include <engine/model/data/gamesysteminitdata.h>
#include <engine/rendering/shaders/shaderinitdata.h>

namespace Monolith
{
#pragma region GeneratedCodeHeader
    class GameRendererInitData : public GameSystemInitData
    {
    public:
        GameRendererInitData();
        ~GameRendererInitData();

        void LoadObject(const ObjectSerializer& serializer) override;

        ShaderInitData GetDefaultShader() const { return m_DefaultShader; }
        void SetDefaultShader(ShaderInitData newValue) { m_DefaultShader = newValue; }

        GameSystem* InstantiateGameSystem() const override;

    private:
        using super = GameSystemInitData;

        ShaderInitData m_DefaultShader;
    };
#pragma endregion //GeneratedCodeHeader
}
