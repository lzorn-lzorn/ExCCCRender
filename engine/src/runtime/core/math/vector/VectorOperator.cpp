#include "runtime/core/math/vector/VectorOperator.h"
#include "runtime/core/math/vector/Vector.hpp"

namespace ExCCCRender::Core::Math {

inline double Dot(const Vector2D& v1, const Vector2D& v2) {
    return v1.Dot(v2);
}

inline double Dot(const Vector3D& v1, const Vector3D& v2) {
    return v1.Dot(v2);
}

inline double Dot(const Vector4D& v1, const Vector4D& v2) {
    return v1.Dot(v2);
}

inline Vector3D Cross(const Vector3D& v1, const Vector3D& v2) {
    return Vector3D(v1.Y() * v2.Z() - v1.Z() * v2.Y(),
                    v1.Z() * v2.X() - v1.X() * v2.Z(),
                    v1.X() * v2.Y() - v1.Y() * v2.Y());
}

inline bool IsParallel(const Vector3D& v1, const Vector3D& v2) {
    return Cross(v1, v2) == ZeroVector3D;
}

inline bool IsParallel(const Vector2D& v1, const Vector2D& v2) {
    return v1.X() * v2.Y() - v1.Y() * v2.X() == 0;
}

inline bool IsVertical(const Vector3D& v1, const Vector3D& v2) {
    return Dot(v1, v2) == 0;
}

inline bool IsVertical(const Vector2D& v1, const Vector2D& v2) {
    return Dot(v1, v2) == 0;
}

inline Vector2D operator+(const Vector2D& v1, const Vector2D& v2) {
    return Vector2D(v1.X() + v2.X(), v1.Y() + v2.Y());
}

inline Vector3D operator+(const Vector3D& v1, const Vector3D& v2) {
    return Vector3D(v1.X() + v2.X(), v1.Y() + v2.Y(), v1.Z() + v2.Z());
}

inline Vector4D operator+(const Vector4D& v1, const Vector4D& v2) {
    return Vector4D(v1.X() + v2.X(), v1.Y() + v2.Y(), v1.Z() + v2.Z(), v1.W() + v2.W());
}

inline Vector2D operator-(const Vector2D& v1, const Vector2D& v2) {
    return Vector2D(v1.X() - v2.X(), v1.Y() - v2.Y());
}

inline Vector3D operator-(const Vector3D& v1, const Vector3D& v2) {
    return Vector3D(v1.X() - v2.X(), v1.Y() - v2.Y(), v1.Z() - v2.Z());
}

inline Vector4D operator-(const Vector4D& v1, const Vector4D& v2) {
    return Vector4D(v1.X() - v2.X(), v1.Y() - v2.Y(), v1.Z() - v2.Z(), v1.W() - v2.W());
}

inline Vector2D operator*(const double ratio, const Vector2D& vec) {
    return Vector2D(vec.X() * ratio, vec.Y() * ratio);
}

inline Vector2D operator*(const Vector2D& vec, const double ratio) {
    return Vector2D(vec.X() * ratio, vec.Y() * ratio);
}

inline Vector3D operator*(const double ratio, const Vector3D& vec) {
    return Vector3D(vec.X() * ratio, vec.Y() * ratio, vec.Z() * ratio);
}

inline Vector3D operator*(const Vector3D& vec, const double ratio) {
    return Vector3D(vec.X() * ratio, vec.Y() * ratio, vec.Z() * ratio);
}

inline Vector4D operator*(const double ratio, const Vector4D& vec) {
    return Vector4D(vec.X() * ratio, vec.Y() * ratio, vec.Z() * ratio, vec.W() * ratio);
}

inline Vector4D operator*(const Vector4D& vec, const double ratio) {
    return Vector4D(vec.X() * ratio, vec.Y() * ratio, vec.Z() * ratio, vec.W() * ratio);
}

inline Vector2D Zoom(const double ratio, const Vector2D& vec) {
    return Vector2D(vec.X() * ratio, vec.Y() * ratio);
}

inline Vector2D Zoom(const Vector2D& vec, const double ratio) {
    return Vector2D(vec.X() * ratio, vec.Y() * ratio);
}

inline Vector3D Zoom(const double ratio, const Vector3D& vec) {
    return Vector3D(vec.X() * ratio, vec.Y() * ratio, vec.Z() * ratio);
}

inline Vector3D Zoom(const Vector3D& vec, const double ratio) {
    return Vector3D(vec.X() * ratio, vec.Y() * ratio, vec.Z() * ratio);
}

inline Vector4D Zoom(const double ratio, const Vector4D& vec) {
    return Vector4D(vec.X() * ratio, vec.Y() * ratio, vec.Z() * ratio, vec.W() * ratio);
}

inline Vector4D Zoom(const Vector4D& vec, const double ratio) {
    return Vector4D(vec.X() * ratio, vec.Y() * ratio, vec.Z() * ratio, vec.W() * ratio);
}
}  // namespace ExCCCRender::Core::Math
