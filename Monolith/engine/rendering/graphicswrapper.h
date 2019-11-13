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

        inline ID3D11Device* GetDevice() const { return m_Device; }
        inline ID3D11DeviceContext* GetDeviceContext() const { return m_DeviceContext; }

        bool Init(s32 screenWidth, s32 screenHeight, bool vsync, HWND windowHandle, bool fullscreen);
        void Shutdown();

        void BeginFrame();
        void EndFrame();

        void SetZBufferActive(bool isActive);
        void SetAlphaBlendingActive(bool isActive);

    private:
        bool m_VSyncEnabled;
        u32 m_VideoCardMemory;
        IDXGISwapChain* m_SwapChain;
        ID3D11Device* m_Device;
        ID3D11DeviceContext* m_DeviceContext;
        ID3D11RenderTargetView* m_RenderTargetView;
        ID3D11Texture2D* m_DepthStencilBuffer;
        ID3D11DepthStencilState* m_DepthStencilState;
        ID3D11DepthStencilState* m_DepthDisabledStencilState;
        ID3D11DepthStencilView* m_DepthStencilView;
        ID3D11RasterizerState* m_RasterState;
        ID3D11BlendState* m_AlphaEnableBlendingState;
        ID3D11BlendState* m_AlphaDisableBlendingState;
    };
}