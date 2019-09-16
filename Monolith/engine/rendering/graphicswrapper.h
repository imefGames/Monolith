#pragma once

// Implementation based off http://www.rastertek.com/tutdx11.html

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <d3dx10math.h>

namespace Monolith
{
    class GraphicsWrapper
    {
    public:
        GraphicsWrapper();
        ~GraphicsWrapper();

        bool Init(s32 screenWidth, s32 screenHeight, bool vsync, HWND windowHandle, bool fullscreen, f32 screenDepth, f32 screenNear);
        void Shutdown();

        void BeginFrame();
        void EndFrame();

        void SetZBufferActive(bool isActive);

    private:
        bool m_VSyncEnabled;
        u32 m_VideoCardMemory;
        IDXGISwapChain* m_SwapChain;
        ID3D11Device* m_Device;
        ID3D11DeviceContext* m_DeviceContext;
        ID3D11RenderTargetView* m_RenderTargetView;
        ID3D11Texture2D* m_DepthStencilBuffer;
        ID3D11DepthStencilState* m_DepthStencilState;
        ID3D11DepthStencilView* m_DepthStencilView;
        ID3D11RasterizerState* m_RasterState;
        D3DXMATRIX m_ProjectionMatrix;
        D3DXMATRIX m_WorldMatrix;
        D3DXMATRIX m_orthoMatrix;
    };
}