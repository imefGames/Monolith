#pragma once

#include <d3d11.h>

namespace Monolith
{
    class GraphicsWrapper;

    class GraphicDeviceData
    {
        friend class GameRenderer;
    public:
        GraphicDeviceData();

        inline ID3D11Device* GetDevice() const { return m_Device; }
        inline ID3D11DeviceContext* GetDeviceContext() const { return m_DeviceContext; }

    private:
        void SetupDevice(const GraphicsWrapper& graphicsWrapper);

        ID3D11Device* m_Device;
        ID3D11DeviceContext* m_DeviceContext;
    };
}