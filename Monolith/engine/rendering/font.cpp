#include <precomp.h>
#include <engine/rendering/font.h>

#include <engine/rendering/dynamicmodel.h>
#include <engine/rendering/texture.h>
#include <fstream>

namespace Monolith
{
    Font::Font()
        : m_Texture{ nullptr }
        , m_FontHeight{ 16.0f }
    {
    }

    Vec2f Font::GetTextSize(const std::string& text) const
    {
        Vec2f size{ 0.0f, m_FontHeight };
        u32 charNumber{ static_cast<u32>(text.size()) };
        for (s8 currentChar : text)
        {
            size[0] += FindFontCharacter(currentChar).m_PixelWidth;
        }
        return size;
    }

    void Font::Initialize(const std::string& textureFileName, const std::string& fontInfoFileName)
    {
        m_Texture = new Texture{};
        m_Texture->Initialize(textureFileName);
        InitializeFontInfo(fontInfoFileName);
    }

    void Font::Shutdown()
    {
        if (m_Texture != nullptr)
        {
            m_Texture->Shutdown();
            delete m_Texture;
            m_Texture = nullptr;
        }

        m_FontCharacters.clear();
    }

    void Font::SetupModel(DynamicModel& model, const std::string& displayedText, const Vec2f& textPosition, const Vec4f& drawColor) const
    {
        u32 charNumber{ static_cast<u32>(displayedText.size()) };
        std::vector<u32>& indexList{ model.GetIndexList() };
        std::vector<Model::VertexType>& vertexList{ model.GetVertexList() };

        indexList.clear();
        vertexList.clear();

        indexList.reserve(static_cast<u64>(charNumber) * 6);
        vertexList.reserve(static_cast<u64>(charNumber) * 4);

        f32 drawX{ textPosition[0] };
        f32 drawY{ textPosition[1] };
        for (u32 currentCharIndex = 0; currentCharIndex < charNumber; ++currentCharIndex)
        {
            const FontCharacter& currentFontCharacter{ FindFontCharacter(displayedText[currentCharIndex]) };
            indexList.push_back(currentCharIndex * 4);
            indexList.push_back(currentCharIndex * 4 + 2);
            indexList.push_back(currentCharIndex * 4 + 1);
            indexList.push_back(currentCharIndex * 4);
            indexList.push_back(currentCharIndex * 4 + 1);
            indexList.push_back(currentCharIndex * 4 + 3);

            vertexList.emplace_back(Vec3f{ drawX, drawY, 0.0f }, drawColor, Vec2f{ currentFontCharacter.m_UVLeft, 0.0f });
            vertexList.emplace_back(Vec3f{ drawX + currentFontCharacter.m_PixelWidth, drawY + m_FontHeight, 0.0f }, drawColor, Vec2f{ currentFontCharacter.m_UVRight, 1.0f });
            vertexList.emplace_back(Vec3f{ drawX + currentFontCharacter.m_PixelWidth, drawY, 0.0f }, drawColor, Vec2f{ currentFontCharacter.m_UVRight, 0.0f });
            vertexList.emplace_back(Vec3f{ drawX, drawY + m_FontHeight, 0.0f }, drawColor, Vec2f{ currentFontCharacter.m_UVLeft, 1.0f });

            drawX += currentFontCharacter.m_PixelWidth;
        }

        model.RefreshBuffers();
    }

    void Font::InitializeFontInfo(const std::string& fontInfoFileName)
    {
        char temp;
        std::ifstream fin;
        fin.open(fontInfoFileName);
        if (!fin.fail())
        {
            m_FontCharacters.resize(K_MAX_CHAR_INDEX);
            while (!fin.eof())
            {
                u32 charIndex{ 0 };
                fin >> charIndex;
            
                fin.get(temp);
                while (temp != ' ')
                {
                    fin.get(temp);
                }
                fin.get(temp);
                while (temp != ' ')
                {
                    fin.get(temp);
                }
            
                FontCharacter& currentFontCharacter{ m_FontCharacters[charIndex] };
                fin >> currentFontCharacter.m_UVLeft;
                fin >> currentFontCharacter.m_UVRight;
                fin >> currentFontCharacter.m_PixelWidth;
            }
            fin.close();
        }
    }

    const Font::FontCharacter& Font::FindFontCharacter(s8 lookupChar) const
    {
        static const FontCharacter nullFontCharacter{};
        return (lookupChar < m_FontCharacters.size() ? m_FontCharacters[lookupChar] : nullFontCharacter);
    }

    Font::FontCharacter::FontCharacter()
        : m_UVLeft{ 0.0f }
        , m_UVRight{ 0.0f }
        , m_PixelWidth{ 0.0f }
    {
    }
}