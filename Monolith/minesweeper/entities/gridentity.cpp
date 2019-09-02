#include <precomp.h>
#include <minesweeper/entities/gridentity.h>

#include <core/serialization/objectserializer.h>
#include <engine/rendering/renderingcontext.h>

namespace Monolith
{
#pragma region GeneratedCodeSource
    GridEntityInitData::GridEntityInitData()
        : super{}
        , m_GridSize{  }
    {
    }

    GridEntityInitData::~GridEntityInitData()
    {
    }

    void GridEntityInitData::LoadObject(const ObjectSerializer& serializer)
    {
        super::LoadObject(serializer);
        ObjectSerializationHelper::LoadObject(serializer["GridSize"], m_GridSize);
    }
#pragma endregion //GeneratedCodeSource

    Entity* GridEntityInitData::InstantiateEntity() const
    {
        return new GridEntity{ *this };
    }



    GridEntity::GridEntity(const GridEntityInitData& gridEntityInitData)
        : Entity{ gridEntityInitData }
        , m_GridSize{ gridEntityInitData.GetGridSize() }
    {
    }

    void GridEntity::Init()
    {
    }

    void GridEntity::Shutdown()
    {
    }

    void GridEntity::Update(f32 deltaTime)
    {
    }

    void GridEntity::Render(RenderingContext& renderingContext)
    {
        Vec2 topLeft{ GetPosition() };
        Vec2 bottomRight{ GetPosition() + m_GridSize + Vec2{ 2.0f, 2.0f } };
        renderingContext.DrawRectangle(topLeft, bottomRight);
    }
}
