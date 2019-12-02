#include <precomp.h>
#include <minesweeper/entities/cameraentity.h>

#include <core/serialization/objectserializer.h>
#include <engine/input/inputprocessor.h>
#include <engine/rendering/renderingcontext.h>

namespace Monolith
{
#pragma region GeneratedCodeSource
    CameraEntityInitData::CameraEntityInitData()
        : super{}
    {
    }

    CameraEntityInitData::~CameraEntityInitData()
    {
    }

    void CameraEntityInitData::LoadObject(const ObjectSerializer& serializer)
    {
        super::LoadObject(serializer);
    }
#pragma endregion //GeneratedCodeSource

    Entity* CameraEntityInitData::InstantiateEntity() const
    {
        return new CameraEntity{ *this };
    }



    CameraEntity::CameraEntity(const CameraEntityInitData& cameraEntityInitData)
        : Entity{ cameraEntityInitData }
    {
    }

    void CameraEntity::Init()
    {
    }

    void CameraEntity::Shutdown()
    {
    }

    void CameraEntity::Render(RenderingContext& renderingContext)
    {
        renderingContext.GetCamera().SetFromPosition(GetPosition());
        renderingContext.GetCamera().SetToPosition(Vec4f{});
    }
}
