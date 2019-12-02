#pragma once

#include <engine/model/entity.h>
#include <engine/model/data/entityinitdata.h>

namespace Monolith
{
#pragma region GeneratedCodeHeader
    class CameraEntityInitData : public EntityInitData
    {
    public:
        CameraEntityInitData();
        ~CameraEntityInitData();

        void LoadObject(const ObjectSerializer& serializer) override;


        Entity* InstantiateEntity() const override;

    private:
        using super = EntityInitData;

    };
#pragma endregion //GeneratedCodeHeader

    class CameraEntity : public Entity
    {
    public:
        CameraEntity(const CameraEntityInitData& cameraEntityInitData);

        void Init() override;
        void Shutdown() override;
        void Render(RenderingContext& renderingContext) override;

    private:
    };
}
