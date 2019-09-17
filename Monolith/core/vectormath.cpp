#include <precomp.h>
#include <core/vectormath.h>

namespace Monolith
{
    namespace Math
    {
        namespace Vector
        {
            Vec3f CrossProduct(const Vec3f& vector1, const Vec3f& vector2)
            {
                return Vec3f
                {
                    vector1[1] * vector2[2] - vector1[2] * vector2[1],
                    vector1[2] * vector2[0] - vector1[0] * vector2[2],
                    vector1[0] * vector2[1] - vector1[1] * vector2[0]
                };
            }
        }
    }
}