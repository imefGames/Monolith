#pragma once

namespace Monolith
{
    class Texture;

    struct TextureHandleContainer
    {
        TextureHandleContainer();

        Texture* m_Texture;
        u32 m_HardRefCount;
    };

    class TextureLoader
    {
        friend class TextureHandle;

    public:
        void LoadPendingTextures();

    private:
        TextureHandleContainer* GetOrCreateTextureHandleContainer(const std::string& texturePath);
        void UnregisterTexture(TextureHandleContainer* textureHandleContainer);

        std::map<std::string, TextureHandleContainer*> m_RegisteredTexture;
        std::map<std::string, TextureHandleContainer*> m_PendingTexture;
    };
}