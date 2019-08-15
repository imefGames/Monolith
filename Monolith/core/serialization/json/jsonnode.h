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
        inline std::string_view GetContentBuffer() const { return m_ContentBuffer; }

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
        template <class T>
        void LoadObject(const JSonNode& node, T& object)
        {
            Report::Assert(false, "[JSonHelper::LoadObject] Not yet implemented");
        }

        template <class T>
        void LoadObject(const JSonNode& node, std::vector<T>& objectVector)
        {
            objectVector.reserve(node.GetSubNodeCount());
            for (const JSonNode& subNode : node)
            {
                T newObject{};
                LoadObject(subNode, newObject);
                objectVector.push_back(newObject);
            }
        }

        void LoadObject(const JSonNode& node, s32& loadedS32);
        void LoadObject(const JSonNode& node, u32& loadedU32);
        void LoadObject(const JSonNode& node, f32& loadedF32);
        void LoadObject(const JSonNode& node, std::string& loadedString);
    }
}