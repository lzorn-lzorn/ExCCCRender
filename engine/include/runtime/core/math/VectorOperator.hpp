#pragma once
#include "runtime/core/traits.hpp"
#include "Vector.h"

namespace ExCCCRender::Core::Math {
    double Dot(const Vector2D&, const Vector2D&);
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

    template <Arithmetic Ty>
    Vector2D operator*(const Ty, const Vector2D&);
    template <Arithmetic Ty>
    Vector2D operator*(const Vector2D&, const Ty);
    template <Arithmetic Ty>
    Vector3D operator*(const Ty, const Vector3D&);
    template <Arithmetic Ty>
    Vector3D operator*(const Vector3D&, const Ty);
    template <Arithmetic Ty>
    Vector4D operator*(const Ty, const Vector4D&);
    template <Arithmetic Ty>
    Vector4D operator*(const Vector4D&, const Ty);

    template <Arithmetic Ty>
    Vector2D Dot(const Ty, const Vector2D&);
    template <Arithmetic Ty>
    Vector2D Dot(const Vector2D&, const Ty);
    template <Arithmetic Ty>
    Vector3D Dot(const Ty, const Vector3D&);
    template <Arithmetic Ty>
    Vector3D Dot(const Vector3D&, const Ty);
    template <Arithmetic Ty>
    Vector4D Dot(const Ty, const Vector4D&);
    template <Arithmetic Ty>
    Vector4D Dot(const Vector4D&, const Ty);
}