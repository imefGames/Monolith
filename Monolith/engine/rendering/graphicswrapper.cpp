#include <precomp.h>
#include <engine/rendering/graphicswrapper.h>

namespace Monolith
{
    GraphicsWrapper::GraphicsWrapper()
        : m_VSyncEnabled{ false }
        , m_VideoCardMemory{ 0 }
        , m_SwapChain{ nullptr }
        , m_Device{ nullptr }
        , m_DeviceContext{ nullptr }
        , m_RenderTargetView{ nullptr }
        , m_DepthStencilBuffer{ nullptr }
        , m_DepthStencilState{ nullptr }
        , m_DepthStencilView{ nullptr }
        , m_RasterState{ nullptr }
    {
    }

    GraphicsWrapper::~GraphicsWrapper()
    {
    }

    bool GraphicsWrapper::Init(s32 screenWidth, s32 screenHeight, bool vsync, HWND windowHandle, bool fullscreen)
    {
        HRESULT result;
        IDXGIFactory* factory{ nullptr };
        IDXGIAdapter* adapter{ nullptr };
        IDXGIOutput* adapterOutput{ nullptr };
        UINT numModes{ 0 };
        size_t stringLength{ 0 };
        DXGI_MODE_DESC* displayModeList{ nullptr };
        DXGI_ADAPTER_DESC adapterDesc;
        s32 error{ 0 };
        ID3D11Texture2D* backBufferPtr{ nullptr };
        D3D11_VIEWPORT viewport;

        m_VSyncEnabled = vsync;
        result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)& factory);
        if (FAILED(result))
        {
            return false;
        }

        result = factory->EnumAdapters(0, &adapter);
        if (FAILED(result))
        {
            return false;
        }

        result = adapter->EnumOutputs(0, &adapterOutput);
        if (FAILED(result))
        {
            return false;
        }

        result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
        if (FAILED(result))
        {
            return false;
        }

        displayModeList = new DXGI_MODE_DESC[numModes];
        if (!displayModeList)
        {
            return false;
        }

        result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
        if (FAILED(result))
        {
            return false;
        }

        u32 numerator{ 0 };
        u32 denominator{ 0 };
        for (u32 i = 0; i < numModes; i++)
        {
            if (displayModeList[i].Width == static_cast<u32>(screenWidth))
            {
                if (displayModeList[i].Height == static_cast<u32>(screenHeight))
                {
                    numerator = displayModeList[i].RefreshRate.Numerator;
                    denominator = displayModeList[i].RefreshRate.Denominator;
                }
            }
        }

        result = adapter->GetDesc(&adapterDesc);
        if (FAILED(result))
        {
            return false;
        }

        m_VideoCardMemory = static_cast<u32>(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

        char videoCardDescription[128];
        error = wcstombs_s(&stringLength, videoCardDescription, 128, adapterDesc.Description, 128);
        if (error != 0)
        {
            return false;
        }

        delete[] displayModeList;
        displayModeList = nullptr;

        adapterOutput->Release();
        adapterOutput = nullptr;

        adapter->Release();
        adapter = nullptr;

        factory->Release();
        factory = nullptr;

        DXGI_SWAP_CHAIN_DESC swapChainDesc;
        ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
        swapChainDesc.BufferCount = 1;
        swapChainDesc.BufferDesc.Width = screenWidth;
        swapChainDesc.BufferDesc.Height = screenHeight;
        swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        if (m_VSyncEnabled)
        {
            swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
            swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
        }
        else
        {
            swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
            swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
        }

        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.OutputWindow = windowHandle;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;
        swapChainDesc.Windowed = !fullscreen;
        swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        swapChainDesc.Flags = 0;

        D3D_FEATURE_LEVEL featureLevel{ D3D_FEATURE_LEVEL_11_0 };
        result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1, D3D11_SDK_VERSION, &swapChainDesc, &m_SwapChain, &m_Device, NULL, &m_DeviceContext);
        if (FAILED(result))
        {
            return false;
        }

        result = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
        if (FAILED(result))
        {
            return false;
        }

        result = m_Device->CreateRenderTargetView(backBufferPtr, NULL, &m_RenderTargetView);
        if (FAILED(result))
        {
            return false;
        }

        backBufferPtr->Release();
        backBufferPtr = nullptr;

        D3D11_TEXTURE2D_DESC depthBufferDesc;
        ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
        depthBufferDesc.Width = screenWidth;
        depthBufferDesc.Height = screenHeight;
        depthBufferDesc.MipLevels = 1;
        depthBufferDesc.ArraySize = 1;
        depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        depthBufferDesc.SampleDesc.Count = 1;
        depthBufferDesc.SampleDesc.Quality = 0;
        depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        depthBufferDesc.CPUAccessFlags = 0;
        depthBufferDesc.MiscFlags = 0;

        result = m_Device->CreateTexture2D(&depthBufferDesc, NULL, &m_DepthStencilBuffer);
        if (FAILED(result))
        {
            return false;
        }

        D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
        ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
        depthStencilDesc.DepthEnable = true;
        depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
        depthStencilDesc.StencilEnable = true;
        depthStencilDesc.StencilReadMask = 0xFF;
        depthStencilDesc.StencilWriteMask = 0xFF;
        depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
        depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
        depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
        depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

        result = m_Device->CreateDepthStencilState(&depthStencilDesc, &m_DepthStencilState);
        if (FAILED(result))
        {
            return false;
        }
        m_DeviceContext->OMSetDepthStencilState(m_DepthStencilState, 1);

        D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
        ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
        depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        depthStencilViewDesc.Texture2D.MipSlice = 0;
        result = m_Device->CreateDepthStencilView(m_DepthStencilBuffer, &depthStencilViewDesc, &m_DepthStencilView);
        if (FAILED(result))
        {
            return false;
        }
        m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

        D3D11_RASTERIZER_DESC rasterDesc;
        rasterDesc.AntialiasedLineEnable = false;
        rasterDesc.CullMode = D3D11_CULL_BACK;
        rasterDesc.DepthBias = 0;
        rasterDesc.DepthBiasClamp = 0.0f;
        rasterDesc.DepthClipEnable = true;
        rasterDesc.FillMode = D3D11_FILL_SOLID;
        rasterDesc.FrontCounterClockwise = false;
        rasterDesc.MultisampleEnable = false;
        rasterDesc.ScissorEnable = false;
        rasterDesc.SlopeScaledDepthBias = 0.0f;
        result = m_Device->CreateRasterizerState(&rasterDesc, &m_RasterState);
        if (FAILED(result))
        {
            return false;
        }
        m_DeviceContext->RSSetState(m_RasterState);

        viewport.Width = static_cast<f32>(screenWidth);
        viewport.Height = static_cast<f32>(screenHeight);
        viewport.MinDepth = 0.0f;
        viewport.MaxDepth = 1.0f;
        viewport.TopLeftX = 0.0f;
        viewport.TopLeftY = 0.0f;
        m_DeviceContext->RSSetViewports(1, &viewport);

        return true;
    }

    void GraphicsWrapper::Shutdown()
    {
        if (m_SwapChain != nullptr)
        {
            m_SwapChain->SetFullscreenState(false, NULL);
        }

        if (m_RasterState != nullptr)
        {
            m_RasterState->Release();
            m_RasterState = nullptr;
        }

        if (m_DepthStencilView != nullptr)
        {
            m_DepthStencilView->Release();
            m_DepthStencilView = nullptr;
        }

        if (m_DepthStencilState != nullptr)
        {
            m_DepthStencilState->Release();
            m_DepthStencilState = nullptr;
        }

        if (m_DepthStencilBuffer != nullptr)
        {
            m_DepthStencilBuffer->Release();
            m_DepthStencilBuffer = nullptr;
        }

        if (m_RenderTargetView != nullptr)
        {
            m_RenderTargetView->Release();
            m_RenderTargetView = nullptr;
        }

        if (m_DeviceContext != nullptr)
        {
            m_DeviceContext->Release();
            m_DeviceContext = nullptr;
        }

        if (m_Device != nullptr)
        {
            m_Device->Release();
            m_Device = nullptr;
        }

        if (m_SwapChain != nullptr)
        {
            m_SwapChain->Release();
            m_SwapChain = nullptr;
        }
    }

    void GraphicsWrapper::BeginFrame()
    {
        float color[4]{ 0.0f, 0.0f, 0.0f, 0.0f };
        m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, color);
        m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
    }

    void GraphicsWrapper::EndFrame()
    {
        m_SwapChain->Present(m_VSyncEnabled ? 1 : 0, 0);
    }

    void GraphicsWrapper::SetZBufferActive(bool isActive)
    {
        m_DeviceContext->OMSetDepthStencilState(m_DepthStencilState, isActive ? 1 : 0);
    }
}