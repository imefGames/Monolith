#pragma once

#include <engine/rendering/camera.h>
#include <engine/rendering/texturehandle.h>

#include <vector>
#include <string>

namespace Monolith
{
    class GraphicsWrapper;
    class DynamicModel;
    class Font;
    class Model;
    class Shader;

    class RenderingContext
    {
        friend class GameRenderer;
        friend class GameWindow;
        friend class RenderPass;

    public:
        RenderingContext();
        ~RenderingContext();

        inline Camera& GetCamera() { return m_Camera; }
        inline const GraphicsWrapper* GetGraphicsWrapper() const { return m_GraphicsWrapper; }
        inline const Mat44f& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        inline const Mat44f& GetViewMatrix() const { return m_ViewMatrix; }
        inline const Mat44f& GetWorldMatrix() const { return m_WorldMatrix; }
        inline const Vec2u& GetWindowSize() const { return m_WindowSize; }

        inline void SetViewMatrix(const Mat44f& viewMatrix) { m_ViewMatrix = viewMatrix; }

        void DrawCharacter2D(const Vec2f& pixelPosition, s8 character);
        void DrawText2D(const Vec2f& textPosition, const std::string& text);
        void DrawRectangle2D(const Vec2f& topLeftPosition, const Vec2f& bottomRightPosition);
        void DrawModel(const Model& model);

        void SetDrawColor(const Vec4f& color);
        void ResetDrawColor();

        const TextureHandle& GetTexture() const;
        void SetTexture(const TextureHandle& texture);

        const Font* GetFont() const;
        void SetFont(const Font* font);

    private:
        void SetWindowSize(u32 windowWidth, u32 windowHeight);

        Mat44f m_ProjectionMatrix;
        Mat44f m_ViewMatrix;
        Mat44f m_WorldMatrix;
        Vec4f m_DrawColor;
        Vec2u m_WindowSize;
        Camera m_Camera;
        GraphicsWrapper* m_GraphicsWrapper;
        Shader* m_CurrentShader;
        Shader* m_DefaultShader;
        DynamicModel* m_AllPurposeModel;
        TextureHandle m_CurrentTexture;
        const Font* m_CurrentFont;
    };
}