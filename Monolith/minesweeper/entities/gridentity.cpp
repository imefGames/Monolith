#include <precomp.h>
#include <minesweeper/entities/gridentity.h>

#include <core/serialization/objectserializer.h>
#include <engine/input/inputprocessor.h>
#include <engine/rendering/gamerenderer.h>
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
        , m_GridSizeX{ static_cast<u32>(gridEntityInitData.GetGridSize()[0]) }
        , m_GridSizeY{ static_cast<u32>(gridEntityInitData.GetGridSize()[1]) }
        , m_MouseClickSlotID{ u32Max }
        , m_RenderCallbackSlotID{ u32Max }
    {
        GenerateGrid();
        m_NullCell.m_visible = true;
    }

    void GridEntity::Init()
    {
        m_RenderCallbackSlotID = GameRenderer::Get()->RegisterRenderCallback(ERenderPass::GUI, this, &GridEntity::Render);
        m_MouseClickSlotID = InputProcessor::Get()->GetMouseClickedSignal().Connect(this, &GridEntity::OnMouseClick);
        m_UnknownCellTexture = TextureHandle{ "minesweeper/textures/tileUnknown.png" };
        m_KnownCellTexture = TextureHandle{ "minesweeper/textures/tileKnown.png" };
        m_BombCellTexture = TextureHandle{ "minesweeper/textures/tileBomb.png" };
    }

    void GridEntity::Shutdown()
    {
        m_BombCellTexture.Release();
        m_KnownCellTexture.Release();
        m_UnknownCellTexture.Release();
        InputProcessor::Get()->GetMouseClickedSignal().Disconnect(m_MouseClickSlotID);
        GameRenderer::Get()->UnregisterRenderCallback(ERenderPass::GUI, m_RenderCallbackSlotID);
    }

    void GridEntity::Update(f32 deltaTime)
    {
    }

    void GridEntity::Render(RenderingContext& renderingContext)
    {
        Vec2f topLeft{ GetPosition() };
        for (u32 j = 0; j < m_GridSizeY; ++j)
        {
            for (u32 i = 0; i < m_GridSizeX; ++i)
            {
                s8 cellValue{ 0 };
                GridEntity::CellStatus& cell{ GetCell(i, j) };
                if (cell.m_visible || cell.m_Value == '*' && MinesweeperGameSystem::Get()->GetGameState() != EMinesweeperGameState::InGame)
                {
                    cellValue = cell.m_Value;
                }
                Vec2f topLeft{ GetPosition() + Vec4f{ i * 16.0f, j * 16.0f } };
                Vec2f bottomRight{ topLeft + Vec2f{ 16.0f, 16.0f } };

                if (cell.m_visible)
                {
                    renderingContext.SetTexture(m_KnownCellTexture);
                }
                else
                {
                    renderingContext.SetTexture(m_UnknownCellTexture);
                }
                renderingContext.DrawRectangle2D(topLeft, bottomRight);

                if (cellValue != 0)
                {
                    if (cellValue == '*')
                    {
                        renderingContext.SetTexture(m_BombCellTexture);
                        renderingContext.DrawRectangle2D(topLeft, bottomRight);
                    }
                    else
                    {
                        renderingContext.SetDrawColor(Vec4f{ 0.0f, 0.0f, 0.0f, 0.0f });
                        renderingContext.DrawCharacter2D(topLeft + Vec2f{ 4.0f, 3.0f }, cellValue);
                        renderingContext.ResetDrawColor();
                    }
                }
            }
        }
    }

    void GridEntity::OnMouseClick(EMouseButton mouseButton, Vec2f clickPosition)
    {
        if (MinesweeperGameSystem::Get()->GetGameState() == EMinesweeperGameState::InGame)
        {
            Vec2f topLeft{ GetPosition() };
            Vec2f bottomRight{ topLeft + Vec2f{ m_GridSizeX * 16.0f, m_GridSizeY * 16.0f } };
            if (clickPosition[0] >= topLeft[0] && clickPosition[0] <= bottomRight[0] &&
                clickPosition[1] >= topLeft[1] && clickPosition[1] <= bottomRight[1])
            {
                u32 clickedCellX{ static_cast<u32>(clickPosition[0] - topLeft[0]) / 16 };
                u32 clickedCellY{ static_cast<u32>(clickPosition[1] - topLeft[1]) / 16 };
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
