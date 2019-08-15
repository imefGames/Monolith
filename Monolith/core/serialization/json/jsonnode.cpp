#include <precomp.h>
#include <core/serialization/json/jsonnode.h>

#include <algorithm>

namespace Monolith
{
    JSonNode JSonNode::ms_NullNode{};

    u64 JSonNode::GetSubNodeCount() const
    {
        return m_ChildNodes.size();
    }

    const JSonNode& JSonNode::operator[](u32 index) const
    {
        return (index < m_ChildNodes.size() ? m_ChildNodes[index] : ms_NullNode);
    }

    const JSonNode& JSonNode::operator[](const char* nodeName) const
    {
        auto findByName{ [nodeName](const JSonNode& currentNode) { return currentNode.GetName() == nodeName; } };
        auto foundNode{ std::find_if(m_ChildNodes.begin(), m_ChildNodes.end(), findByName) };
        return (foundNode != m_ChildNodes.end() ? *foundNode : ms_NullNode);
    }

    namespace JSonHelper
    {
        void LoadObject(const JSonNode& node, s32& loadedS32)
        {
            //Not ideal, this copies the string view to a temporary string.
            loadedS32 = std::stol(node.GetContentBuffer().data());
        }

        void LoadObject(const JSonNode& node, u32& loadedU32)
        {
            //Not ideal, this copies the string view to a temporary string.
            loadedU32 = std::stoul(node.GetContentBuffer().data());
        }

        void LoadObject(const JSonNode& node, f32& loadedF32)
        {
            //Not ideal, this copies the string view to a temporary string.
            loadedF32 = std::stof(node.GetContentBuffer().data());
        }

        void LoadObject(const JSonNode& node, std::string& loadedString)
        {
            loadedString = node.GetContentBuffer();
        }
    }
}