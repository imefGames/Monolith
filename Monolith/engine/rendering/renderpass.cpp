#include <precomp.h>
#include <engine/rendering/renderpass.h>

#include <core/serialization/objectserializer.h>
#include <engine/model/universe.h>
#include <engine/rendering/graphicswrapper.h>
#include <engine/rendering/renderingcontext.h>

namespace Monolith
{
    const f32 K_SCREEN_DEPTH = 1000.0f;
    const f32 K_SCREEN_NEAR = 0.1f;
    const f32 K_FIELD_OF_VIEW = Math::PI / 4.0f;

#pragma region GeneratedCodeSource
    RenderPassInitData::RenderPassInitData()
        : super{}
        , m_RenderPassID{ 0 }
        , m_ProjectionMatrixType{ 0 }
        , m_ZBufferActive{ true }
        , m_AlphaBlendingActive{ false }
    {
    }

    RenderPassInitData::~RenderPassInitData()
    {
    }

    void RenderPassInitData::LoadObject(const ObjectSerializer& serializer)
    {
        super::LoadObject(serializer);
        ObjectSerializationHelper::LoadObject(serializer["RenderPassID"], m_RenderPassID);
        ObjectSerializationHelper::LoadObject(serializer["ProjectionMatrixType"], m_ProjectionMatrixType);
        ObjectSerializationHelper::LoadObject(serializer["ZBufferActive"], m_ZBufferActive);
        ObjectSerializationHelper::LoadObject(serializer["AlphaBlendingActive"], m_AlphaBlendingActive);
    }
#pragma endregion //GeneratedCodeSource

    RenderPass* RenderPassInitData::InstantiateRenderPass() const
    {
        return new RenderPass{ *this };
    }



    RenderPass::RenderPass(const RenderPassInitData& passData)
        : m_RenderPass{ static_cast<ERenderPass>(passData.GetRenderPassID()) }
        , m_ProjectionMatrixType{ static_cast<ERenderPassProjection>(passData.GetProjectionMatrixType()) }
        , m_ZBufferActive{ passData.GetZBufferActive() }
        , m_AlphaBlendingActive{ passData.GetAlphaBlendingActive() }
    {
    }

    void RenderPass::Render(RenderingContext& renderingContext)
    {
        const Vec2u& windowSize{ renderingContext.GetWindowSize() };
        switch (m_ProjectionMatrixType)
        {
            case ERenderPassProjection::Perspective:
            {
                renderingContext.m_ProjectionMatrix = Math::Matrix::PerspectiveProjection(K_FIELD_OF_VIEW, static_cast<f32>(windowSize[0]) / static_cast<f32>(windowSize[1]), K_SCREEN_NEAR, K_SCREEN_DEPTH);
                break;
            }
            break;
            case ERenderPassProjection::Orthographic:
            {
                renderingContext.m_ProjectionMatrix = Math::Matrix::OrthographicProjection(0.0f, 0.0f, static_cast<f32>(windowSize[0]), static_cast<f32>(windowSize[1]), K_SCREEN_NEAR, K_SCREEN_DEPTH);
                break;
            }
            default:
            {
                Report::Assert(false, "Invalid Render Pass Type.");
                break;
            }
        }

        GraphicsWrapper* graphicsWrapper{ renderingContext.m_GraphicsWrapper };
        graphicsWrapper->SetZBufferActive(m_ZBufferActive);
        graphicsWrapper->SetAlphaBlendingActive(m_AlphaBlendingActive);


        //TODO: allow entities & systems to register to pass rather than parse all renderable classes.
        Universe::Get()->Render(renderingContext);
    }
}
