#include <precomp.h>
#include <engine/rendering/graphicdevicedata.h>

#include <engine/rendering/graphicswrapper.h>

namespace Monolith
{
    GraphicDeviceData::GraphicDeviceData()
        : m_Device{ nullptr }
        , m_DeviceContext{ nullptr }
    {
    }

    void GraphicDeviceData::SetupDevice(const GraphicsWrapper& graphicsWrapper)
    {
        m_Device = graphicsWrapper.GetDevice();
        m_DeviceContext = graphicsWrapper.GetDeviceContext();
    }
}