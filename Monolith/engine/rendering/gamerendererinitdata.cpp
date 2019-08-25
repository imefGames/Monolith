#include <precomp.h>
#include <engine/rendering/gamerendererinitdata.h>

#include <core/serialization/objectserializer.h>
#include <engine/rendering/gamerenderer.h>

namespace Monolith
{
#pragma region GeneratedCodeSource
    GameRendererInitData::GameRendererInitData()
        : super{}
    {
    }

    GameRendererInitData::~GameRendererInitData()
    {
    }

    void GameRendererInitData::LoadObject(const ObjectSerializer& serializer)
    {
        super::LoadObject(serializer);
    }
#pragma endregion //GeneratedCodeSource

    GameSystem* GameRendererInitData::InstanciateGameSystem() const
    {
        return new GameRenderer();
    }
}
