#pragma once

namespace Monolith
{
    class Camera
    {
    public:
        inline const Mat44f& GetViewMatrix() const { return m_ViewMatrix; }
        inline void SetFromPosition(const Vec4f& fromPosition) { m_FromPosition = fromPosition; }
        inline void SetToPosition(const Vec4f& toPosition) { m_ToPosition = toPosition; }

        void ComputeViewMatrix();

    private:
        Vec4f m_FromPosition;
        Vec4f m_ToPosition;
        Mat44f m_ViewMatrix;
    };
}