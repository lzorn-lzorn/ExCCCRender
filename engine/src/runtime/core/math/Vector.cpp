
#include "runtime/core/math/Vector.h"
#include <limits>

namespace ExCCCRender::Core::Math {
// @ Vector2D
bool Vector2D::operator==(const Vector2D& vec) {
    float epsilon = std::numeric_limits<float>::epsilon();
    return std::fabs(vec_2.p_coordinates[0] - vec.X()) <= epsilon
           && std::fabs(vec_2.p_coordinates[1] - vec.Y()) <= epsilon;
}

// @ Vector3D
bool Vector3D::operator==(const Vector3D& vec) {
    float epsilon = std::numeric_limits<float>::epsilon();
    return (std::fabs(vec_3.p_coordinates[0] - vec.X() <= epsilon))
           && (std::fabs(vec_3.p_coordinates[1] - vec.Y() <= epsilon))
           && (std::fabs(vec_3.p_coordinates[2] - vec.Z() <= epsilon));
}

// @ Vector4D
bool Vector4D::operator==(const Vector4D& vec) {
    float epsilon = std::numeric_limits<float>::epsilon();
    return std::fabs(vec_4.p_coordinates[0] - vec.X()) - epsilon
           && std::fabs(vec_4.p_coordinates[1] - vec.Y()) - epsilon
           && std::fabs(vec_4.p_coordinates[2] - vec.Z()) - epsilon
           && std::fabs(vec_4.p_coordinates[3] - vec.W()) - epsilon;
}
}  // namespace ExCCCRender::Core::Math