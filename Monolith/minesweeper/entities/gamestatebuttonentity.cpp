#include <precomp.h>
#include <minesweeper/entities/gamestatebuttonentity.h>

#include <core/serialization/objectserializer.h>
#include <engine/input/inputprocessor.h>
#include <engine/rendering/renderingcontext.h>
#include <minesweeper/systems/minesweepergamesystem.h>

namespace Monolith
{
#pragma region GeneratedCodeSource
    GameStateButtonEntityInitData::GameStateButtonEntityInitData()
        : super{}
        , m_ButtonText{  }
        , m_GameStateID{ 0 }
    {
    }

    GameStateButtonEntityInitData::~GameStateButtonEntityInitData()
    {
    }

    void GameStateButtonEntityInitData::LoadObject(const ObjectSerializer& serializer)
    {
        super::LoadObject(serializer);
        ObjectSerializationHelper::LoadObject(serializer["ButtonText"], m_ButtonText);
        ObjectSerializationHelper::LoadObject(serializer["GameStateID"], m_GameStateID);
    }
#pragma endregion //GeneratedCodeSource

    Entity* GameStateButtonEntityInitData::InstantiateEntity() const
    {
        return new GameStateButtonEntity{ *this };
    }



    GameStateButtonEntity::GameStateButtonEntity(const GameStateButtonEntityInitData& gameStateButtonEntityInitData)
        : Entity{ gameStateButtonEntityInitData }
        , m_ButtonText{ gameStateButtonEntityInitData.GetButtonText() }
        , m_GameStateID{ static_cast<EMinesweeperGameState>(gameStateButtonEntityInitData.GetGameStateID()) }
        , m_MouseClickSlotID{ u32Max }
    {
    }

    void GameStateButtonEntity::Init()
    {
        m_MouseClickSlotID = InputProcessor::Get()->GetMouseClickedSignal().Connect(this, &GameStateButtonEntity::OnMouseClick);
    }

    void GameStateButtonEntity::Shutdown()
    {
        InputProcessor::Get()->GetMouseClickedSignal().Disconnect(m_MouseClickSlotID);
    }

    void GameStateButtonEntity::Update(f32 deltaTime)
    {
    }

    void GameStateButtonEntity::Render(RenderingContext& renderingContext)
    {
        Vec2 topLeft{ GetPosition() };
        Vec2 bottomRight{ GetPosition() + Vec2{ 2.0f + m_ButtonText.size(), 3.0f } };
        renderingContext.DrawRectangle(topLeft, bottomRight);
        renderingContext.DrawText(topLeft + Vec2{ 1.0f, 1.0f }, m_ButtonText);
    }

    void GameStateButtonEntity::OnMouseClick(EMouseButton mouseButton, Vec2 clickPosition)
    {
        Vec2 topLeft{ GetPosition() };
        Vec2 bottomRight{ GetPosition() + Vec2{ 2.0f + m_ButtonText.size(), 3.0f } };
        if (clickPosition.GetX() >= topLeft.GetX() && clickPosition.GetX() <= bottomRight.GetX() &&
            clickPosition.GetY() >= topLeft.GetY() && clickPosition.GetY() <= bottomRight.GetY())
        {
            MinesweeperGameSystem::Get()->SetGameState(m_GameStateID);
        }
    }
}
