#include <precomp.h>
#include <minesweeper/entities/cameraentity.h>

#include <core/serialization/objectserializer.h>
#include <engine/input/inputprocessor.h>
#include <engine/rendering/gamerenderer.h>
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
        , m_RenderCallbackSlotID{ u32Max }
    {
    }

    void CameraEntity::Init()
    {
        m_RenderCallbackSlotID = GameRenderer::Get()->RegisterRenderCallback(ERenderPass::World, this, &CameraEntity::Render);
    }

    void CameraEntity::Shutdown()
    {
        GameRenderer::Get()->UnregisterRenderCallback(ERenderPass::World, m_RenderCallbackSlotID);
    }

    void CameraEntity::Render(RenderingContext& renderingContext)
    {
        renderingContext.GetCamera().SetFromPosition(GetPosition());
        renderingContext.GetCamera().SetToPosition(Vec4f{});
        renderingContext.GetCamera().ComputeViewMatrix();
        renderingContext.SetViewMatrix(renderingContext.GetCamera().GetViewMatrix());
    }
}
