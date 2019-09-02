#include <precomp.h>
#include <minesweeper/entities/gridentity.h>

#include <core/serialization/objectserializer.h>
#include <engine/input/inputprocessor.h>
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
        , m_MouseClickSlotID{ u32Max }
    {
    }

    void GridEntity::Init()
    {
        m_MouseClickSlotID = InputProcessor::Get()->GetMouseClickedSignal().Connect(this, &GridEntity::OnMouseClick);
    }

    void GridEntity::Shutdown()
    {
        InputProcessor::Get()->GetMouseClickedSignal().Disconnect(m_MouseClickSlotID);
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

    void GridEntity::OnMouseClick(EMouseButton mouseButton, Vec2 clickPosition)
    {
        Vec2 topLeft{ GetPosition() + Vec2{ 1.0f, 1.0f } };
        Vec2 bottomRight{ GetPosition() + m_GridSize + Vec2{ 1.0f, 1.0f } };
        if (clickPosition.GetX() >= topLeft.GetX() && clickPosition.GetX() <= bottomRight.GetX() &&
            clickPosition.GetY() >= topLeft.GetY() && clickPosition.GetY() <= bottomRight.GetY())
        {
            u32 clickedCellX{ static_cast<u32>(clickPosition.GetX() - topLeft.GetX()) };
            u32 clickedCellY{ static_cast<u32>(clickPosition.GetY() - topLeft.GetY()) };
            HandleCellClick(clickedCellX, clickedCellY);
        }
    }

    void GridEntity::HandleCellClick(u32 cellX, u32 cellY)
    {

    }
}
