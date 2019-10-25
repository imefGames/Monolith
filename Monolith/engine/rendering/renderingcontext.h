#pragma once

#include <engine/rendering/camera.h>

#include <vector>
#include <string>

namespace Monolith
{
    class GraphicsWrapper;
    class Model;
    class Shader;

    class RenderingContext
    {
        friend class GameRenderer;
        friend class GameWindow;

    public:
        RenderingContext();

        inline const GraphicsWrapper* GetGraphicsWrapper() const { return m_GraphicsWrapper; }
        inline const Mat44f& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        inline const Mat44f& GetViewMatrix() const { return m_ViewMatrix; }
        inline const Mat44f& GetWorldMatrix() const { return m_WorldMatrix; }

        void DrawCharacter2D(const Vec2f& pixelPosition, s8 character);
        void DrawText2D(const Vec2f& textPosition, const std::string& text);
        void DrawRectangle2D(const Vec2f& topLeftPosition, const Vec2f& bottomRightPosition);
        void DrawModel(const Model& model);

    private:
        void SetWindowSize(u32 windowWidth, u32 windowHeight);

        Mat44f m_ProjectionMatrix;
        Mat44f m_ViewMatrix;
        Mat44f m_WorldMatrix;
        Camera m_Camera;
        GraphicsWrapper* m_GraphicsWrapper;
        Shader* m_CurrentShader;
        Shader* m_DefaultShader;
    };
}