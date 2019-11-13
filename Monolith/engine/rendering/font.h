#pragma once

#include <vector>

namespace Monolith
{
    class Texture;
    class DynamicModel;

    class Font
    {
    public:
        Font();

        inline const Texture* GetFontTexture() const { return m_Texture; }

        void Initialize(const std::string& textureFileName, const std::string& fontInfoFileName);
        void Shutdown();
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

        Texture* m_Texture;
        std::vector<FontCharacter> m_FontCharacters;
        f32 m_FontHeight;
    };
}