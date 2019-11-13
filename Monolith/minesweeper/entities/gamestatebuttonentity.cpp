#include <precomp.h>
#include <minesweeper/entities/gamestatebuttonentity.h>

#include <core/serialization/objectserializer.h>
#include <engine/input/inputprocessor.h>
#include <engine/rendering/font.h>
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
        , m_ButtonSize{}
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
        if (const Font* currentFont = renderingContext.GetFont())
        {
            m_ButtonSize = currentFont->GetTextSize(m_ButtonText);
        }

        Vec2f topLeft{ GetPosition() };
        Vec2f bottomRight{ GetPosition() + m_ButtonSize };
        renderingContext.DrawRectangle2D(topLeft, bottomRight);
        renderingContext.DrawText2D(topLeft, m_ButtonText);
    }

    void GameStateButtonEntity::OnMouseClick(EMouseButton mouseButton, Vec2f clickPosition)
    {
        Vec2f topLeft{ GetPosition() };
        Vec2f bottomRight{ GetPosition() + m_ButtonSize };
        if (clickPosition[0] >= topLeft[0] && clickPosition[0] <= bottomRight[0] &&
            clickPosition[1] >= topLeft[1] && clickPosition[1] <= bottomRight[1])
        {
            MinesweeperGameSystem::Get()->SetGameState(m_GameStateID);
        }
    }
}
