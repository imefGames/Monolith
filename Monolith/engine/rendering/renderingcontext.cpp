#include <precomp.h>
#include <engine/rendering/renderingcontext.h>

#include <engine/rendering/model.h>
#include <engine/rendering/shaders/shader.h>

namespace Monolith
{
    RenderingContext::RenderingContext()
        : m_GraphicsWrapper{ nullptr }
        , m_CurrentShader{ nullptr }
        , m_DefaultShader{ nullptr }
    {
    }

    void RenderingContext::SetWindowSize(u32 windowWidth, u32 windowHeight)
    {
    }

    void RenderingContext::DrawCharacter2D(const Vec2f& pixelPosition, s8 character)
    {
    }

    void RenderingContext::DrawText2D(const Vec2f& textPosition, const std::string& text)
    {
    }

    void RenderingContext::DrawRectangle2D(const Vec2f& topLeftPosition, const Vec2f& bottomRightPosition)
    {
    }

    void RenderingContext::DrawModel(const Model& model)
    {
        if (m_CurrentShader != nullptr)
        {
            model.SetupRender(*this);
            m_CurrentShader->Render(*this, model.GetIndexCount());
        }
    }
}