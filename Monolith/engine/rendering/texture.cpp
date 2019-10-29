#include <precomp.h>
#include <engine/rendering/texture.h>

#include <engine/rendering/gamerenderer.h>

namespace Monolith
{
    Texture::Texture()
        : m_Texture{ nullptr }
    {
    }

    void Texture::Initialize(const std::string& fileName)
    {
        ID3D11Device* device{ GameRenderer::Get()->GetGraphicDeviceData().GetDevice() };
        D3DX11CreateShaderResourceViewFromFile(device, fileName.c_str(), NULL, NULL, &m_Texture, NULL);
    }

    void Texture::Shutdown()
    {
        if (m_Texture != nullptr)
        {
            m_Texture->Release();
            m_Texture = nullptr;
        }
    }
}