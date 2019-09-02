#pragma once

#include <engine/model/entity.h>
#include <engine/model/data/entityinitdata.h>

namespace Monolith
{
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
        Vec2 m_GridSize;
    };
}
