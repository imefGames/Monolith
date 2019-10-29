#pragma once

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>

namespace Monolith
{
    class RenderingContext;
    class ShaderInitData;

    class Shader
    {
    private:
        struct MatrixBufferType
        {
            Mat44f m_WorldMatrix;
            Mat44f m_ViewMatrix;
            Mat44f m_ProjectionMatrix;
        };

    public:
        Shader();

        void Init(const ShaderInitData& defaultShaderInitData);
        void Shutdown();
        void Render(const RenderingContext& renderingContext, s32 indexCount);

    private:
        void SetShaderParameters(const RenderingContext& renderingContext);
        void RenderShader(const RenderingContext& renderingContext, s32 indexCount);

    private:
        ID3D11VertexShader* m_VertexShader;
        ID3D11PixelShader* m_PixelShader;
        ID3D11InputLayout* m_Layout;
        ID3D11Buffer* m_MatrixBuffer;
        ID3D11SamplerState* m_SampleState;
    };
}