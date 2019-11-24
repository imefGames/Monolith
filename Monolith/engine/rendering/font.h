#pragma once

#include <vector>
#include <engine/rendering/texturehandle.h>

namespace Monolith
{
    class DynamicModel;

    class Font
    {
    public:
        Font(const std::string& textureFileName, const std::string& fontInfoFileName);
        ~Font();

        inline const TextureHandle& GetFontTexture() const { return m_Texture; }
        Vec2f GetTextSize(const std::string& text) const;

        void SetupModel(DynamicModel& model, const std::string& displayedText, const Vec2f& textPosition, const Vec4f& drawColor) const;

    private:
        struct FontCharacter
        {
            FontCharacter();

            f32 m_UVLeft;
            f32 m_UVRight;
            f32 m_PixelWidth;
        };

        void InitializeFontInfo(const std::string& fontInfoFileName);
        const FontCharacter& FindFontCharacter(s8 lookupChar) const;

        static constexpr u32 K_MAX_CHAR_INDEX{ 256 };

        TextureHandle m_Texture;
        std::vector<FontCharacter> m_FontCharacters;
        f32 m_FontHeight;
    };
}