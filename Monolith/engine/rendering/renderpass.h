#pragma once

#include <engine/model/object.h>

namespace Monolith
{
    class RenderingContext;
    class RenderPass;

    enum class ERenderPass
    {
        World,
        GUI
    };

    enum class ERenderPassProjection
    {
        Perspective,
        Orthographic
    };

#pragma region GeneratedCodeHeader
    class RenderPassInitData : public Object
    {
    public:
        RenderPassInitData();
        ~RenderPassInitData();

        void LoadObject(const ObjectSerializer& serializer) override;

        u32 GetRenderPassID() const { return m_RenderPassID; }
        void SetRenderPassID(u32 newValue) { m_RenderPassID = newValue; }
        u32 GetProjectionMatrixType() const { return m_ProjectionMatrixType; }
        void SetProjectionMatrixType(u32 newValue) { m_ProjectionMatrixType = newValue; }
        bool GetZBufferActive() const { return m_ZBufferActive; }
        void SetZBufferActive(bool newValue) { m_ZBufferActive = newValue; }
        bool GetAlphaBlendingActive() const { return m_AlphaBlendingActive; }
        void SetAlphaBlendingActive(bool newValue) { m_AlphaBlendingActive = newValue; }

        RenderPass* InstantiateRenderPass() const;

    private:
        using super = Object;

        u32 m_RenderPassID;
        u32 m_ProjectionMatrixType;
        bool m_ZBufferActive;
        bool m_AlphaBlendingActive;
    };
#pragma endregion //GeneratedCodeHeader

    class RenderPass
    {
    public:
        RenderPass(const RenderPassInitData& passData);

        void Render(RenderingContext& renderingContext);

    private:
        ERenderPass m_RenderPass;
        ERenderPassProjection m_ProjectionMatrixType;
        bool m_ZBufferActive;
        bool m_AlphaBlendingActive;
    };
}
