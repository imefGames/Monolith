#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace Monolith
{
    class JSonNode
    {
    public:
        u64 GetSubNodeCount() const;
        inline std::string_view GetName() const { return m_Name; }
        inline void SetName(std::string_view name) { m_Name = name; }
        inline std::string_view GetContentBuffer() const { return m_ContentBuffer; }
        inline void SetContentBuffer(std::string_view contentBuffer) { m_ContentBuffer = contentBuffer; }

        JSonNode& AddSubNode();

        const JSonNode& operator[](u32 index) const;
        const JSonNode& operator[](const char* nodeName) const;

    private:
        static JSonNode ms_NullNode;

        std::vector<JSonNode> m_ChildNodes;
        std::string_view m_Name;
        std::string_view m_ContentBuffer;
    };

    namespace JSonHelper
    {
        void LoadObject(const JSonNode& node, s32& loadedS32);
        void LoadObject(const JSonNode& node, u32& loadedU32);
        void LoadObject(const JSonNode& node, f32& loadedF32);
        void LoadObject(const JSonNode& node, std::string& loadedString);
    }
}