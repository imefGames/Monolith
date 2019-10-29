#pragma once

#include <d3d11.h>
#include <d3dx11tex.h>

namespace Monolith
{
    class Texture
    {
    public:
        Texture();

        void Initialize(const std::string& fileName);
        void Shutdown();

    private:
        ID3D11ShaderResourceView* m_Texture;
    };
}