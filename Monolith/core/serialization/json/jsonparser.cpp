#include <precomp.h>
#include <core/serialization/json/jsonparser.h>

#include <algorithm>
#include <cctype>
#include <iterator>

namespace Monolith
{
    namespace JSonParserInternal
    {
        enum class ETokenType
        {
            None,
            Number,
            String,
            ReservedSymbol
        };

        struct ParserToken
        {
            std::string_view m_Token;
            ETokenType m_TokenType = ETokenType::None;
        };

        bool FindNextToken(ParserToken& token, std::string_view& buffer)
        {
            bool foundToken{ false };
            buffer.remove_prefix(std::min(buffer.find_first_not_of("\t\n\v\f\r "), buffer.size()));

            if (!buffer.empty())
            {
                char currentChar{ buffer[0] };
                const char reservedSymbols[]{ "{}[],:" };
                if (std::find(std::begin(reservedSymbols), std::end(reservedSymbols), currentChar) != std::end(reservedSymbols))
                {
                    token.m_TokenType = ETokenType::ReservedSymbol;
                    token.m_Token = std::string_view{ buffer.data(), 1 };
                    buffer.remove_prefix(1);
                    foundToken = true;
                }
                else if (currentChar == '"')
                {
                    //TODO: handle \" in string.
                    buffer.remove_prefix(1);
                    u64 stringEndPos{ buffer.find_first_of('"') };
                    if (stringEndPos != std::string_view::npos)
                    {
                        token.m_TokenType = ETokenType::String;
                        token.m_Token = std::string_view{ buffer.data(), stringEndPos };
                        buffer.remove_prefix(stringEndPos + 1);
                        foundToken = true;
                    }
                    else
                    {
                        Report::Assert(false, "[JSON] String never ends.");
                    }
                }
                else if (std::isdigit(currentChar) || currentChar == '-')
                {
                    u64 numberEnd{ buffer.find_first_not_of("0123456789", 1) };
                    if (numberEnd != std::string_view::npos && buffer[numberEnd] == '.')
                    {
                        numberEnd = buffer.find_first_not_of("0123456789", numberEnd + 1);
                    }

                    numberEnd = std::min(numberEnd, buffer.size());
                    if (numberEnd != 1 || currentChar != '-')
                    {
                        token.m_TokenType = ETokenType::Number;
                        token.m_Token = std::string_view{ buffer.data(), numberEnd };
                        buffer.remove_prefix(numberEnd);
                        foundToken = true;
                    }
                    else
                    {
                        Report::Assert(false, "[JSON] Unexpected Symbol '-'.");
                    }
                }
                else
                {
                    //TODO: specify symbol.
                    Report::Assert(false, "[JSON] Unexpected Symbol.");
                }
            }

            return foundToken;
        }

        bool PeekNextToken(ParserToken& token, std::string_view buffer)
        {
            return FindNextToken(token, buffer);
        }

        void BuildNamedObjectNode(JSonNode& node, std::string_view& contentBuffer);

        void BuildObjectNode(JSonNode& node, std::string_view& contentBuffer)
        {
            ParserToken currentToken{};
            FindNextToken(currentToken, contentBuffer);
            if (currentToken.m_TokenType == ETokenType::ReservedSymbol)
            {
                if (currentToken.m_Token == "{")
                {
                    PeekNextToken(currentToken, contentBuffer);
                    if (currentToken.m_Token == "}")
                    {
                        FindNextToken(currentToken, contentBuffer);
                        //End of Object
                    }
                    else
                    {
                        BuildNamedObjectNode(node.AddSubNode(), contentBuffer);
                        PeekNextToken(currentToken, contentBuffer);
                        while (currentToken.m_Token != "}")
                        {
                            if (currentToken.m_Token == ",")
                            {
                                FindNextToken(currentToken, contentBuffer);
                                //Next Property
                            }
                            else
                            {
                                BuildNamedObjectNode(node.AddSubNode(), contentBuffer);
                            }
                            PeekNextToken(currentToken, contentBuffer);
                        }
                        FindNextToken(currentToken, contentBuffer);
                    }
                }
                else if (currentToken.m_Token == "[")
                {
                    PeekNextToken(currentToken, contentBuffer);
                    if (currentToken.m_Token == "]")
                    {
                        FindNextToken(currentToken, contentBuffer);
                        //End of array
                    }
                    else
                    {
                        BuildObjectNode(node.AddSubNode(), contentBuffer);
                        PeekNextToken(currentToken, contentBuffer);
                        while (currentToken.m_Token != "]")
                        {
                            if (currentToken.m_Token == ",")
                            {
                                FindNextToken(currentToken, contentBuffer);
                                //Next Object
                            }
                            else
                            {
                                BuildObjectNode(node.AddSubNode(), contentBuffer);
                            }
                            PeekNextToken(currentToken, contentBuffer);
                        }
                        FindNextToken(currentToken, contentBuffer);
                    }
                }
                else
                {
                    //TODO: specify symbol.
                    Report::Assert(false, "[JSON] Unexpected Symbol.");
                }
            }
            else
            {
                node.SetContentBuffer(currentToken.m_Token);
            }
        }

        void BuildNamedObjectNode(JSonNode& node, std::string_view& contentBuffer)
        {
            ParserToken currentToken{};
            FindNextToken(currentToken, contentBuffer);
            if (currentToken.m_TokenType == ETokenType::String)
            {
                node.SetName(currentToken.m_Token);
                FindNextToken(currentToken, contentBuffer);
                if (currentToken.m_Token == ":")
                {
                    BuildObjectNode(node, contentBuffer);
                }
                else
                {
                    //TODO: specify symbol.
                    Report::Assert(false, "[JSON] Unexpected Symbol.");
                }
            }
            else
            {
                //TODO: specify symbol.
                Report::Assert(false, "[JSON] Unexpected Symbol.");
            }
        }
    }

    JSonParser::JSonParser(const std::string& contentBuffer)
        : m_ContentBuffer{ contentBuffer }
    {
        std::string_view content{ m_ContentBuffer };
        JSonParserInternal::BuildObjectNode(m_RootNode, content);
    }
}