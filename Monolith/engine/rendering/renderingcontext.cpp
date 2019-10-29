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
        , m_AllPurposeModel{ new Model{} }
        , m_CurrentTexture{ nullptr }
        , m_DrawColor{ 1.0f, 1.0f, 1.0f, 1.0f }
    {
    }

    RenderingContext::~RenderingContext()
    {
        m_AllPurposeModel->Shutdown();
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
        //TODO: cache vertex buffer to limit allocation.
        std::vector<u32> indexList{ 0, 2, 1, 0, 1, 3 };
        std::vector<Model::VertexType> vertexList
        {
            { Vec3f{ topLeftPosition[0], topLeftPosition[1], 0.0f }, m_DrawColor, Vec2f{ 0.0f, 0.0f } } ,
            { Vec3f{ bottomRightPosition[0], bottomRightPosition[1], 0.0f }, m_DrawColor, Vec2f{ 1.0f, 1.0f } } ,
            { Vec3f{ bottomRightPosition[0], topLeftPosition[1], 0.0f }, m_DrawColor, Vec2f{ 1.0f, 0.0f } } ,
            { Vec3f{ topLeftPosition[0], bottomRightPosition[1], 0.0f }, m_DrawColor, Vec2f{ 0.0f, 1.0f } }
        };

        m_AllPurposeModel->SetVertexList(vertexList, indexList);
        DrawModel(*m_AllPurposeModel);
    }

    void RenderingContext::DrawModel(const Model& model)
    {
        if (m_CurrentShader != nullptr)
        {
            model.SetupRender(*this);
            m_CurrentShader->Render(*this, model.GetIndexCount());
        }
    }

    void RenderingContext::SetDrawColor(const Vec4f& color)
    {
        m_DrawColor = color;
    }

    void RenderingContext::ResetDrawColor()
    {
        m_DrawColor = Vec4f{ 1.0f, 1.0f, 1.0f, 1.0f };
    }

    const Texture* RenderingContext::GetTexture() const
    {
        return m_CurrentTexture;
    }

    void RenderingContext::SetTexture(const Texture* texture)
    {
        m_CurrentTexture = texture;
    }
}