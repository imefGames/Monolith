#include <precomp.h>
#include <engine/rendering/model.h>

#include <engine/rendering/gamerenderer.h>
#include <engine/rendering/graphicswrapper.h>
#include <engine/rendering/renderingcontext.h>

namespace Monolith
{
    Model::VertexType::VertexType(const Vec3f& position, const Vec4f& color, const Vec2f& texturePosition)
        : m_Position{ position }
        , m_Color{ color }
        , m_TexturePosition{ texturePosition }
    {
    }

    Model::Model()
        :m_IndexBuffer{ nullptr }
        , m_VertexBuffer{ nullptr }
        , m_VertexCount{ 0 }
        , m_IndexCount{ 0 }
    {
    }

    void Model::SetVertexList(const std::vector<Model::VertexType>& vertexList, const std::vector<u32>& indexList)
    {
        CleanBuffers();

        m_VertexCount = static_cast<s32>(vertexList.size());
        m_IndexCount = static_cast<s32>(indexList.size());

        D3D11_BUFFER_DESC vertexBufferDesc;
        vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_VertexCount;
        vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        vertexBufferDesc.CPUAccessFlags = 0;
        vertexBufferDesc.MiscFlags = 0;
        vertexBufferDesc.StructureByteStride = 0;

        D3D11_SUBRESOURCE_DATA vertexData;
        vertexData.pSysMem = vertexList.data();
        vertexData.SysMemPitch = 0;
        vertexData.SysMemSlicePitch = 0;

        ID3D11Device* device{ GameRenderer::Get()->GetGraphicDeviceData().GetDevice() };
        HRESULT result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_VertexBuffer);
        if (FAILED(result))
        {
            return;
        }

        D3D11_BUFFER_DESC indexBufferDesc;
        indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_IndexCount;
        indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        indexBufferDesc.CPUAccessFlags = 0;
        indexBufferDesc.MiscFlags = 0;
        indexBufferDesc.StructureByteStride = 0;

        D3D11_SUBRESOURCE_DATA indexData;
        indexData.pSysMem = indexList.data();
        indexData.SysMemPitch = 0;
        indexData.SysMemSlicePitch = 0;

        result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_IndexBuffer);
    }

    void Model::CleanBuffers()
    {
        if (m_IndexBuffer != nullptr)
        {
            m_IndexBuffer->Release();
            m_IndexBuffer = nullptr;
        }
        if (m_VertexBuffer != nullptr)
        {
            m_VertexBuffer->Release();
            m_VertexBuffer = nullptr;
        }
    }

    void Model::Shutdown()
    {
        CleanBuffers();
    }

    void Model::SetupRender(const RenderingContext& renderingContext) const
    {
        unsigned int stride{ sizeof(VertexType) };
        unsigned int offset{ 0 };
        ID3D11DeviceContext* deviceContext{ renderingContext.GetGraphicsWrapper()->GetDeviceContext() };
        deviceContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
        deviceContext->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
        deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    }
}