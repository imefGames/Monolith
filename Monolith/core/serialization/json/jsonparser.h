#pragma once

#include <core/serialization/json/jsonnode.h>
#include <string>

namespace Monolith
{
    class JSonParser
    {
    public:
        JSonParser(const std::string& contentBuffer);

    private:
        JSonNode m_RootNode;
        std::string m_ContentBuffer;
    };
}