#pragma once

#include <engine/rendering/model.h>

namespace Monolith
{
    class DynamicModel : public Model
    {
    public:
        std::vector<u32>& GetIndexList() { return m_IndexList; }
        std::vector<Model::VertexType>& GetVertexList() { return m_VertexList; }
        void RefreshBuffers();

    private:
        std::vector<u32> m_IndexList;
        std::vector<Model::VertexType> m_VertexList;
    };
}