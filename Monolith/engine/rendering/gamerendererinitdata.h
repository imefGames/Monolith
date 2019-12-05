#pragma once

#include <engine/model/data/gamesysteminitdata.h>
#include <engine/rendering/renderpass.h>
#include <engine/rendering/shaders/shaderinitdata.h>

namespace Monolith
{
    using RenderPassInitDataArray = std::vector<RenderPassInitData>;
    using RenderPassInitDataOutputArray = const std::vector<RenderPassInitData>&;

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
        RenderPassInitDataOutputArray GetRenderPasses() const;

    private:
        using super = GameSystemInitData;

        ShaderInitData m_DefaultShader;
        RenderPassInitDataArray m_RenderPasses;
    };
#pragma endregion //GeneratedCodeHeader
}
