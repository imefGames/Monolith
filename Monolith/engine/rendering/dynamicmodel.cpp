#include <precomp.h>
#include <engine/rendering/dynamicmodel.h>

namespace Monolith
{
    void DynamicModel::RefreshBuffers()
    {
        SetVertexList(m_VertexList, m_IndexList);
    }
}