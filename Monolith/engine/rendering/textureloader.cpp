#include <precomp.h>
#include <engine/rendering/textureloader.h>

#include <engine/rendering/texture.h>

namespace Monolith
{
    TextureHandleContainer::TextureHandleContainer()
        : m_Texture{ nullptr }
        , m_HardRefCount{ 0 }
    {
    }

    TextureHandleContainer* TextureLoader::GetOrCreateTextureHandleContainer(const std::string& texturePath)
    {
        TextureHandleContainer* textureHandleContainer{ nullptr };
        auto foundContainer{ m_RegisteredTexture.find(texturePath) };
        if (foundContainer != m_RegisteredTexture.end())
        {
            textureHandleContainer = foundContainer->second;
        }
        else
        {
            textureHandleContainer = new TextureHandleContainer{};
            m_RegisteredTexture[texturePath] = textureHandleContainer;
            m_PendingTexture[texturePath] = textureHandleContainer;
        }
        return textureHandleContainer;
    }

    void TextureLoader::UnregisterTexture(TextureHandleContainer* textureHandleContainer)
    {
        //TODO: move deletions to later ?
        for (const auto& registeredContainer : m_RegisteredTexture)
        {
            if (registeredContainer.second == textureHandleContainer)
            {
                m_RegisteredTexture.erase(registeredContainer.first);
                break;
            }
        }

        textureHandleContainer->m_Texture->Shutdown();
        delete textureHandleContainer->m_Texture;
        delete textureHandleContainer;
    }

    void TextureLoader::LoadPendingTextures()
    {
        for (const auto& pendingContainer : m_PendingTexture)
        {
            Texture* newTexture{ new Texture{} };
            newTexture->Initialize(pendingContainer.first);
            pendingContainer.second->m_Texture = newTexture;
        }
        m_PendingTexture.clear();
    }
}