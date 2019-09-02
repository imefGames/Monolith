#include <precomp.h>
#include <minesweeper/entities/gridentity.h>

#include <core/serialization/objectserializer.h>
#include <engine/input/inputprocessor.h>
#include <engine/rendering/renderingcontext.h>
#include <minesweeper/systems/minesweepergamesystem.h>
#include <stdlib.h>

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
        , m_GridSizeX{ static_cast<u32>(gridEntityInitData.GetGridSize().GetX()) }
        , m_GridSizeY{ static_cast<u32>(gridEntityInitData.GetGridSize().GetY()) }
        , m_MouseClickSlotID{ u32Max }
    {
        GenerateGrid();
        m_NullCell.m_visible = true;
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
        Vec2 bottomRight{ GetPosition() + Vec2{ m_GridSizeX + 2.0f, m_GridSizeY + 2.0f } };
        renderingContext.DrawRectangle(topLeft, bottomRight);

        for (u32 j = 0; j < m_GridSizeY; ++j)
        {
            for (u32 i = 0; i < m_GridSizeX; ++i)
            {
                s8 cellValue{ -80 };
                GridEntity::CellStatus& cell{ GetCell(i, j) };
                if (cell.m_visible || MinesweeperGameSystem::Get()->GetGameState() != EMinesweeperGameState::InGame)
                {
                    cellValue = cell.m_Value;
                }
                renderingContext.DrawCharacter(topLeft + Vec2{ i + 1.0f, j + 1.0f }, cellValue);
            }
        }
    }

    void GridEntity::OnMouseClick(EMouseButton mouseButton, Vec2 clickPosition)
    {
        if (MinesweeperGameSystem::Get()->GetGameState() == EMinesweeperGameState::InGame)
        {
            Vec2 topLeft{ GetPosition() + Vec2{ 1.0f, 1.0f } };
            Vec2 bottomRight{ GetPosition() + Vec2{ m_GridSizeX + 1.0f, m_GridSizeY + 1.0f } };
            if (clickPosition.GetX() >= topLeft.GetX() && clickPosition.GetX() <= bottomRight.GetX() &&
                clickPosition.GetY() >= topLeft.GetY() && clickPosition.GetY() <= bottomRight.GetY())
            {
                u32 clickedCellX{ static_cast<u32>(clickPosition.GetX() - topLeft.GetX()) };
                u32 clickedCellY{ static_cast<u32>(clickPosition.GetY() - topLeft.GetY()) };
                RevealCell(clickedCellX, clickedCellY);
                UpdateGameState();
            }
        }
    }

    void GridEntity::RevealCell(u32 cellX, u32 cellY)
    {
        GridEntity::CellStatus& cell{ GetCell(cellX, cellY) };
        if (!cell.m_visible)
        {
            cell.m_visible = true;
            if (cell.m_Value == ' ')
            {
                for (u32 j = 0; j < 3; ++j)
                {
                    for (u32 i = 0; i < 3; ++i)
                    {
                        RevealCell(cellX + i - 1, cellY + j - 1);
                    }
                }
            }
        }
    }

    GridEntity::CellStatus& GridEntity::GetCell(u32 cellX, u32 cellY)
    {
        if (cellX < m_GridSizeX && cellY < m_GridSizeY)
        {
            u32 cellPosition = (cellX + m_GridSizeX * cellY);
            if (cellPosition < m_Cells.size())
            {
                return m_Cells[cellPosition];
            }
        }
        return m_NullCell;
    }

    void GridEntity::GenerateGrid()
    {
        m_Cells.resize(static_cast<u64>(m_GridSizeX) * m_GridSizeY);

        for (u32 i = 0; i < 10; ++i)
        {
            bool positionnedBomb{ false };
            while (!positionnedBomb)
            {
                u32 cellX{ std::rand() % m_GridSizeX };
                u32 cellY{ std::rand() % m_GridSizeY };
                GridEntity::CellStatus& cell{ GetCell(cellX, cellY) };
                if (cell.m_Value != '*')
                {
                    cell.m_Value = '*';
                    positionnedBomb = true;
                }
            }
        }

        for (u32 j = 0; j < m_GridSizeY; ++j)
        {
            for (u32 i = 0; i < m_GridSizeX; ++i)
            {
                GridEntity::CellStatus& currentCell{ GetCell(i, j) };
                if (currentCell.m_Value != '*')
                {
                    s8 value{ '0' };
                    for (u32 dy = 0; dy < 3; ++dy)
                    {
                        for (u32 dx = 0; dx < 3; ++dx)
                        {
                            if (dx != 1 || dy != 1)
                            {
                                GridEntity::CellStatus& cell{ GetCell(i + dx - 1, j + dy - 1) };
                                if (cell.m_Value == '*')
                                {
                                    ++value;
                                }
                            }
                        }
                    }
                    currentCell.m_Value = (value != '0' ? value : ' ');
                }
            }
        }
    }

    void GridEntity::UpdateGameState()
    {
        bool gameWon{ true };
        bool gameLost{ false };
        for (GridEntity::CellStatus& cell : m_Cells)
        {
            if (cell.m_Value == '*')
            {
                if (cell.m_visible)
                {
                    gameWon = true;
                    break;
                }
            }
            else
            {
                if (!cell.m_visible)
                {
                    gameWon = false;
                }
            }
        }

        if (gameLost)
        {
            MinesweeperGameSystem::Get()->SetGameState(EMinesweeperGameState::Failure);
        }
        else if (gameWon)
        {
            MinesweeperGameSystem::Get()->SetGameState(EMinesweeperGameState::Victory);
        }
    }
}
