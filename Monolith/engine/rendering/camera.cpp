#include <precomp.h>
#include <engine/rendering/camera.h>

namespace Monolith
{
    void Camera::ComputeViewMatrix()
    {
        Vec4f tmp{ 0.0f, 1.0f, 0.0f };
        Vec4f forward = Math::Vector::Normalize(m_FromPosition - m_ToPosition);
        Vec4f right = Math::Vector::CrossProduct(tmp, forward);
        Vec4f up = Math::Vector::CrossProduct(forward, right);

        m_ViewMatrix = Mat44f{};
        m_ViewMatrix(0, 0) = right[0];
        m_ViewMatrix(0, 1) = right[1];
        m_ViewMatrix(0, 2) = right[2];
        m_ViewMatrix(1, 0) = up[0];
        m_ViewMatrix(1, 1) = up[1];
        m_ViewMatrix(1, 2) = up[2];
        m_ViewMatrix(2, 0) = forward[0];
        m_ViewMatrix(2, 1) = forward[1];
        m_ViewMatrix(2, 2) = forward[2];
        m_ViewMatrix(3, 0) = m_FromPosition[0];
        m_ViewMatrix(3, 1) = m_FromPosition[1];
        m_ViewMatrix(3, 2) = m_FromPosition[2];
    }
}