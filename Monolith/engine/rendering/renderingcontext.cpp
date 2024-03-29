#include <precomp.h>
#include <engine/rendering/renderingcontext.h>

#include <engine/rendering/dynamicmodel.h>
#include <engine/rendering/font.h>
#include <engine/rendering/shaders/shader.h>

namespace Monolith
{
    RenderingContext::RenderingContext()
        : m_GraphicsWrapper{ nullptr }
        , m_CurrentShader{ nullptr }
        , m_DefaultShader{ nullptr }
        , m_AllPurposeModel{ new DynamicModel{} }
        , m_CurrentTexture{}
        , m_CurrentFont{ nullptr }
        , m_DrawColor{ 1.0f, 1.0f, 1.0f, 1.0f }
    {
    }

    RenderingContext::~RenderingContext()
    {
        m_AllPurposeModel->Shutdown();
    }

    void RenderingContext::SetWindowSize(u32 windowWidth, u32 windowHeight)
    {
        m_WindowSize = Vec2u{ windowWidth, windowHeight };
    }

    void RenderingContext::DrawCharacter2D(const Vec2f& pixelPosition, s8 character)
    {
        std::string text{ character };
        DrawText2D(pixelPosition, text);
    }

    void RenderingContext::DrawText2D(const Vec2f& textPosition, const std::string& text)
    {
        if (m_CurrentFont != nullptr)
        {
            TextureHandle cachedTexture{ m_CurrentTexture };
            m_CurrentTexture = m_CurrentFont->GetFontTexture();
            m_CurrentFont->SetupModel(*m_AllPurposeModel, text, textPosition, m_DrawColor);
            DrawModel(*m_AllPurposeModel);
            m_CurrentTexture = cachedTexture;
        }
        else
        {
            Report::Warning(false, "Requesting Text rendering without a font.");
        }
    }

    void RenderingContext::DrawRectangle2D(const Vec2f& topLeftPosition, const Vec2f& bottomRightPosition)
    {
        std::vector<u32>& indexList{ m_AllPurposeModel->GetIndexList() };
        indexList.clear();
        indexList.push_back(0);
        indexList.push_back(2);
        indexList.push_back(1);
        indexList.push_back(0);
        indexList.push_back(1);
        indexList.push_back(3);

        std::vector<Model::VertexType>& vertexList{ m_AllPurposeModel->GetVertexList() };
        vertexList.clear();
        vertexList.emplace_back(Vec3f{ topLeftPosition[0], topLeftPosition[1], 0.0f }, m_DrawColor, Vec2f{ 0.0f, 0.0f });
        vertexList.emplace_back(Vec3f{ bottomRightPosition[0], bottomRightPosition[1], 0.0f }, m_DrawColor, Vec2f{ 1.0f, 1.0f });
        vertexList.emplace_back(Vec3f{ bottomRightPosition[0], topLeftPosition[1], 0.0f }, m_DrawColor, Vec2f{ 1.0f, 0.0f });
        vertexList.emplace_back(Vec3f{ topLeftPosition[0], bottomRightPosition[1], 0.0f }, m_DrawColor, Vec2f{ 0.0f, 1.0f });
        m_AllPurposeModel->RefreshBuffers();
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

    const TextureHandle& RenderingContext::GetTexture() const
    {
        return m_CurrentTexture;
    }

    void RenderingContext::SetTexture(const TextureHandle& texture)
    {
        m_CurrentTexture = texture;
    }

    const Font* RenderingContext::GetFont() const
    {
        return m_CurrentFont;
    }

    void RenderingContext::SetFont(const Font* font)
    {
        m_CurrentFont = font;
    }
}