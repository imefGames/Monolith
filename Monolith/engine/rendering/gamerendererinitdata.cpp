#include <precomp.h>
#include <engine/rendering/gamerendererinitdata.h>

#include <core/serialization/objectserializer.h>
#include <engine/rendering/gamerenderer.h>

namespace Monolith
{
#pragma region GeneratedCodeSource
    GameRendererInitData::GameRendererInitData()
        : super{}
        , m_DefaultShader{  }
        , m_RenderPasses{  }
    {
    }

    GameRendererInitData::~GameRendererInitData()
    {
    }

    void GameRendererInitData::LoadObject(const ObjectSerializer& serializer)
    {
        super::LoadObject(serializer);
        ObjectSerializationHelper::LoadObject(serializer["DefaultShader"], m_DefaultShader);
        ObjectSerializationHelper::LoadObject(serializer["RenderPasses"], m_RenderPasses);
    }
#pragma endregion //GeneratedCodeSource

    GameSystem* GameRendererInitData::InstantiateGameSystem() const
    {
        return new GameRenderer(*this);
    }

    RenderPassInitDataOutputArray GameRendererInitData::GetRenderPasses() const
    {
        return m_RenderPasses;
    }
}
