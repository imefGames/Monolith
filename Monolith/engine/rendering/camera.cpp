#include <precomp.h>
#include <engine/rendering/camera.h>

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>

namespace Monolith
{
    void Camera::ComputeViewMatrix()
    {
        Vec4f tmp{ 0.0f, 1.0f, 0.0f };
        Vec4f forward = Math::Vector::Normalize(m_ToPosition - m_FromPosition);
        Vec4f right = Math::Vector::CrossProduct(tmp, forward);
        Vec4f up = Math::Vector::CrossProduct(forward, right);

        Mat44f rotation{
            right[0], up[0], forward[0], 0.0f,
            right[1], up[1], forward[1], 0.0f,
            right[2], up[2], forward[2], 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        Mat44f translation{
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            -m_FromPosition[0], -m_FromPosition[1], -m_FromPosition[2], 1.0f,
        };
        m_ViewMatrix = Math::Matrix::Multiply(rotation, translation);
    }
}