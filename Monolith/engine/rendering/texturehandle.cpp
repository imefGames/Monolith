#include <precomp.h>
#include <engine/rendering/texturehandle.h>

#include <engine/rendering/gamerenderer.h>
#include <engine/rendering/texture.h>
#include <engine/rendering/textureloader.h>

namespace Monolith
{
    TextureHandle::TextureHandle()
        : m_HandleContainer{ false }
    {
    }

    TextureHandle::TextureHandle(const std::string& texturePath)
    {
        m_HandleContainer = GameRenderer::Get()->GetTextureLoader().GetOrCreateTextureHandleContainer(texturePath);
        ++m_HandleContainer->m_HardRefCount;
        //TODO: handle multithreading
    }

    TextureHandle::~TextureHandle()
    {
        Release();
    }

    TextureHandle::TextureHandle(const TextureHandle& otherHandle)
    {
        Release();
        m_HandleContainer = otherHandle.m_HandleContainer;
        ++m_HandleContainer->m_HardRefCount;
    }

    TextureHandle& TextureHandle::operator=(const TextureHandle& otherHandle)
    {
        Release();
        m_HandleContainer = otherHandle.m_HandleContainer;
        ++m_HandleContainer->m_HardRefCount;
        return *this;
    }

    const Texture* TextureHandle::GetTexture() const
    {
        const Texture* texture{ nullptr };
        if (m_HandleContainer != nullptr)
        {
            texture = m_HandleContainer->m_Texture;
        }
        return texture;
    }

    void TextureHandle::Release()
    {
        if (m_HandleContainer)
        {
            //TODO: handle multithreading
            --m_HandleContainer->m_HardRefCount;
            if (m_HandleContainer->m_HardRefCount == 0)
            {
                GameRenderer::Get()->GetTextureLoader().UnregisterTexture(m_HandleContainer);
                m_HandleContainer = nullptr;
            }
        }
    }
}