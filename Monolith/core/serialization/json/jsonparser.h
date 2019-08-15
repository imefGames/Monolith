#pragma once

#include <core/serialization/json/jsonnode.h>
#include <string>

namespace Monolith
{
    class JSonParser
    {
    public:
        JSonParser(const std::string& contentBuffer);

        inline const JSonNode& GetRootNode() const { return m_RootNode; }

    private:
        JSonNode m_RootNode;
        std::string m_ContentBuffer;
    };
}