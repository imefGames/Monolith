#pragma once

#include <d3d11.h>
#include <d3dx10math.h>

namespace Monolith
{
    class RenderingContext;

    class Model
    {
    public:
        struct VertexType
        {
            VertexType(const Vec3f& position, const Vec4f& color);

            Vec3f m_Position;
            Vec4f m_Color;
        };

        Model();

        void SetVertexList(const std::vector<Model::VertexType>& vertexList, const std::vector<u32>& indexList);
        void CleanBuffers();
        void Shutdown();
        void SetupRender(const RenderingContext& renderingContext);

        inline s32 GetIndexCount() const { return m_IndexCount; }

    private:
        ID3D11Buffer* m_IndexBuffer;
        ID3D11Buffer* m_VertexBuffer;
        s32 m_VertexCount;
        s32 m_IndexCount;
    };
}