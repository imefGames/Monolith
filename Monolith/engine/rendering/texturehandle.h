#pragma once

namespace Monolith
{
    class Texture;
    struct TextureHandleContainer;

    class TextureHandle
    {
    public:
        TextureHandle();
        TextureHandle(const std::string& texturePath);
        TextureHandle(const TextureHandle& otherHandle);
        ~TextureHandle();
        TextureHandle& operator=(const TextureHandle& otherHandle);

        const Texture* GetTexture() const;

        void Release();

    private:
        TextureHandleContainer* m_HandleContainer;
    };
}