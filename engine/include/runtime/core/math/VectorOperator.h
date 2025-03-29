#pragma once
#include "runtime/core/traits.hpp"
#include "tools/static_for.hpp"
#include "Vector.h"

namespace ExCCCRender::Core::Math {
    double Dot(const Vector2D& v1, const Vector2D& v2){
    }
    double Dot(const Vector3D&, const Vector3D&);
    double Dot(const Vector4D&, const Vector4D&);
    // 只有三维向量才有叉积
    Vector3D Cross(const Vector3D&, const Vector3D&);

    bool IsParallel(const Vector3D&, const Vector3D&);
    bool IsParallel(const Vector2D&, const Vector2D&);
    bool IsVertical(const Vector3D&, const Vector3D&);
    bool IsVertical(const Vector2D&, const Vector2D&);

    Vector2D operator+(const Vector2D&, const Vector2D&);
    Vector3D operator+(const Vector3D&, const Vector3D&);
    Vector4D operator+(const Vector4D&, const Vector4D&);

    Vector2D operator-(const Vector2D&, const Vector2D&);
    Vector3D operator-(const Vector3D&, const Vector3D&);
    Vector4D operator-(const Vector4D&, const Vector4D&);

    Vector2D operator*(const float, const Vector2D&);
    Vector2D operator*(const Vector2D&, const float);
    Vector3D operator*(const float, const Vector3D&);
    Vector3D operator*(const Vector3D&, const float);
    Vector4D operator*(const float, const Vector4D&);
    Vector4D operator*(const Vector4D&, const float);

    Vector2D Dot(const float, const Vector2D&);
    Vector2D Dot(const Vector2D&, const float);
    Vector3D Dot(const float, const Vector3D&);
    Vector3D Dot(const Vector3D&, const float);
    Vector4D Dot(const float, const Vector4D&);
    Vector4D Dot(const Vector4D&, const float);
}