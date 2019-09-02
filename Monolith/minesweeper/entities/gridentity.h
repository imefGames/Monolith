#pragma once

#include <engine/model/entity.h>
#include <engine/model/data/entityinitdata.h>
#include <vector>

namespace Monolith
{
    enum class EMouseButton;

#pragma region GeneratedCodeHeader
    class GridEntityInitData : public EntityInitData
    {
    public:
        GridEntityInitData();
        ~GridEntityInitData();

        void LoadObject(const ObjectSerializer& serializer) override;

        Vec2 GetGridSize() const { return m_GridSize; }
        void SetGridSize(Vec2 newValue) { m_GridSize = newValue; }

        Entity* InstantiateEntity() const override;

    private:
        using super = EntityInitData;

        Vec2 m_GridSize;
    };
#pragma endregion //GeneratedCodeHeader

    class GridEntity : public Entity
    {
    public:
        GridEntity(const GridEntityInitData& gridEntityInitData);

        void Init() override;
        void Shutdown() override;
        void Update(f32 deltaTime) override;
        void Render(RenderingContext& renderingContext) override;

    private:
        struct CellStatus
        {
            s8 m_Value = ' ';
            bool m_visible = false;
        };

        void OnMouseClick(EMouseButton mouseButton, Vec2 clickPosition);
        void RevealCell(u32 cellX, u32 cellY);
        CellStatus& GetCell(u32 cellX, u32 cellY);
        void GenerateGrid();
        void UpdateGameState();

        u32 m_GridSizeX;
        u32 m_GridSizeY;
        u32 m_MouseClickSlotID;
        std::vector<CellStatus> m_Cells;
        CellStatus m_NullCell;
    };
}
