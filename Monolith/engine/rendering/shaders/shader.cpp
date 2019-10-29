#include <precomp.h>
#include <engine/rendering/shaders/shader.h>

#include <engine/rendering/gamerenderer.h>
#include <engine/rendering/graphicswrapper.h>
#include <engine/rendering/renderingcontext.h>
#include <engine/rendering/texture.h>

namespace Monolith
{
    Shader::Shader()
        : m_VertexShader{ nullptr }
        , m_PixelShader{ nullptr }
        , m_Layout{ nullptr }
        , m_MatrixBuffer{ nullptr }
        , m_SampleState{ nullptr }
    {
    }


    void Shader::Init(const ShaderInitData& defaultShaderInitData)
    {
        ID3D11Device* device{ GameRenderer::Get()->GetGraphicDeviceData().GetDevice() };
        ID3D10Blob* errorMessage{ nullptr };
        ID3D10Blob* vertexShaderBuffer{ nullptr };
        ID3D10Blob* pixelShaderBuffer{ nullptr };

        HRESULT result = D3DX11CompileFromFile("engine/rendering/shaders/texture.vs", NULL, NULL, "TextureVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &vertexShaderBuffer, &errorMessage, NULL);
        if (FAILED(result))
        {
            return;
        }

        result = D3DX11CompileFromFile("engine/rendering/shaders/texture.ps", NULL, NULL, "TexturePixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &pixelShaderBuffer, &errorMessage, NULL);
        if (FAILED(result))
        {
            return;
        }

        result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_VertexShader);
        if (FAILED(result))
        {
            return;
        }

        result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_PixelShader);
        if (FAILED(result))
        {
            return;
        }

        D3D11_INPUT_ELEMENT_DESC polygonLayout[3];
        polygonLayout[0].SemanticName = "POSITION";
        polygonLayout[0].SemanticIndex = 0;
        polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
        polygonLayout[0].InputSlot = 0;
        polygonLayout[0].AlignedByteOffset = 0;
        polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        polygonLayout[0].InstanceDataStepRate = 0;

        polygonLayout[1].SemanticName = "COLOR";
        polygonLayout[1].SemanticIndex = 0;
        polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        polygonLayout[1].InputSlot = 0;
        polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
        polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        polygonLayout[1].InstanceDataStepRate = 0;

        polygonLayout[2].SemanticName = "TEXCOORD";
        polygonLayout[2].SemanticIndex = 0;
        polygonLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
        polygonLayout[2].InputSlot = 0;
        polygonLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
        polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        polygonLayout[2].InstanceDataStepRate = 0;

        s32 numElements{ sizeof(polygonLayout) / sizeof(polygonLayout[0]) };
        result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_Layout);
        if (FAILED(result))
        {
            return;
        }

        vertexShaderBuffer->Release();
        vertexShaderBuffer = nullptr;

        pixelShaderBuffer->Release();
        pixelShaderBuffer = nullptr;

        D3D11_BUFFER_DESC matrixBufferDesc;
        matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
        matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
        matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        matrixBufferDesc.MiscFlags = 0;
        matrixBufferDesc.StructureByteStride = 0;
        result = device->CreateBuffer(&matrixBufferDesc, NULL, &m_MatrixBuffer);
        if (FAILED(result))
        {
            return;
        }

        D3D11_SAMPLER_DESC samplerDesc;
        samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.MipLODBias = 0.0f;
        samplerDesc.MaxAnisotropy = 1;
        samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
        samplerDesc.BorderColor[0] = 0;
        samplerDesc.BorderColor[1] = 0;
        samplerDesc.BorderColor[2] = 0;
        samplerDesc.BorderColor[3] = 0;
        samplerDesc.MinLOD = 0;
        samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
        result = device->CreateSamplerState(&samplerDesc, &m_SampleState);
    }


    void Shader::Shutdown()
    {
        if (m_SampleState != nullptr)
        {
            m_SampleState->Release();
            m_SampleState = nullptr;
        }
        if (m_MatrixBuffer != nullptr)
        {
            m_MatrixBuffer->Release();
            m_MatrixBuffer = nullptr;
        }
        if (m_Layout != nullptr)
        {
            m_Layout->Release();
            m_Layout = nullptr;
        }
        if (m_PixelShader != nullptr)
        {
            m_PixelShader->Release();
            m_PixelShader = nullptr;
        }
        if (m_VertexShader != nullptr)
        {
            m_VertexShader->Release();
            m_VertexShader = nullptr;
        }
    }

    void Shader::Render(const RenderingContext& renderingContext, s32 indexCount)
    {
        SetShaderParameters(renderingContext);
        RenderShader(renderingContext, indexCount);
    }

    void Shader::SetShaderParameters(const RenderingContext& renderingContext)
    {
        ID3D11DeviceContext* deviceContext{ renderingContext.GetGraphicsWrapper()->GetDeviceContext() };
        D3D11_MAPPED_SUBRESOURCE mappedResource;
        HRESULT result = deviceContext->Map(m_MatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
        if (FAILED(result))
        {
            return;
        }

        MatrixBufferType* dataPtr{ reinterpret_cast<MatrixBufferType*>(mappedResource.pData) };
        dataPtr->m_WorldMatrix = Math::Matrix::Transpose(renderingContext.GetWorldMatrix());
        dataPtr->m_ViewMatrix = Math::Matrix::Transpose(renderingContext.GetViewMatrix());
        dataPtr->m_ProjectionMatrix = Math::Matrix::Transpose(renderingContext.GetProjectionMatrix());

        deviceContext->Unmap(m_MatrixBuffer, 0);
        u32 bufferNumber = 0;
        deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_MatrixBuffer);
        if (const Texture* texture = renderingContext.GetTexture())
        {
            deviceContext->PSSetShaderResources(0, 1, texture->GetResourceView());
        }
    }


    void Shader::RenderShader(const RenderingContext& renderingContext, s32 indexCount)
    {
        ID3D11DeviceContext* deviceContext{ renderingContext.GetGraphicsWrapper()->GetDeviceContext() };
        deviceContext->IASetInputLayout(m_Layout);
        deviceContext->VSSetShader(m_VertexShader, NULL, 0);
        deviceContext->PSSetShader(m_PixelShader, NULL, 0);
        deviceContext->PSSetSamplers(0, 1, &m_SampleState);
        deviceContext->DrawIndexed(indexCount, 0, 0);
    }
}