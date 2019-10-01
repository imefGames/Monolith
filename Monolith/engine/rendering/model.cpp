#include <precomp.h>
#include <engine/rendering/model.h>

#include <engine/rendering/graphicswrapper.h>
#include <engine/rendering/renderingcontext.h>

namespace Monolith
{
    Model::Model()
        :m_IndexBuffer{ nullptr }
        , m_VertexBuffer{ nullptr }
        , m_VertexCount{ 0 }
        , m_IndexCount{ 0 }
    {
    }

    void Model::Init(const RenderingContext& renderingContext)
    {
        m_VertexCount = 3;
        m_IndexCount = 3;

        VertexType* vertices{ new VertexType[m_VertexCount] };
        u32* indices{ new u32[m_IndexCount] };

        vertices[0].m_Position = Vec3f{ -1.0f, -1.0f, 0.0f };
        vertices[0].m_Color = Vec4f{ 0.0f, 1.0f, 0.0f, 1.0f };

        vertices[1].m_Position = Vec3f{ 0.0f, 1.0f, 0.0f };
        vertices[1].m_Color = Vec4f{ 0.0f, 1.0f, 0.0f, 1.0f };

        vertices[2].m_Position = Vec3f{ 1.0f, -1.0f, 0.0f };
        vertices[2].m_Color = Vec4f{ 0.0f, 1.0f, 0.0f, 1.0f };

        indices[0] = 0;
        indices[1] = 1;
        indices[2] = 2;

        D3D11_BUFFER_DESC vertexBufferDesc;
        vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_VertexCount;
        vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        vertexBufferDesc.CPUAccessFlags = 0;
        vertexBufferDesc.MiscFlags = 0;
        vertexBufferDesc.StructureByteStride = 0;

        D3D11_SUBRESOURCE_DATA vertexData;
        vertexData.pSysMem = vertices;
        vertexData.SysMemPitch = 0;
        vertexData.SysMemSlicePitch = 0;

        ID3D11Device* device{ renderingContext.GetGraphicsWrapper()->GetDevice() };
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
        indexData.pSysMem = indices;
        indexData.SysMemPitch = 0;
        indexData.SysMemSlicePitch = 0;

        result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_IndexBuffer);
        if (FAILED(result))
        {
            return;
        }
        delete[] vertices;
        delete[] indices;
    }

    void Model::Shutdown()
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

    void Model::SetupRender(const RenderingContext& renderingContext)
    {
        unsigned int stride{ sizeof(VertexType) };
        unsigned int offset{ 0 };
        ID3D11DeviceContext* deviceContext{ renderingContext.GetGraphicsWrapper()->GetDeviceContext() };
        deviceContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
        deviceContext->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
        deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    }
}