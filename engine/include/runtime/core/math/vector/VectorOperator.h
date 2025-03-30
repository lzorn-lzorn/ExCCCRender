#pragma once
#include <iostream>
#include <format>
#include "Vector.hpp"

namespace ExCCCRender::Core::Math {
const Vector2D ZeroVector2D(0.0f, 0.0f);
const Vector3D ZeroVector3D(0.0f, 0.0f, 0.0f);
const Vector4D ZeroVector4D(0.0f, 0.0f, 0.0f, 0.0f);
const Vector2D AxisX2D(1.0f, 0.0f);
const Vector2D AxisY2D(0.0f, 1.0f);
const Vector3D AxisX3D(1.0f, 0.0f, 0.0f);
const Vector3D AxisY3D(0.0f, 1.0f, 0.0f);
const Vector3D AxisZ3D(0.0f, 0.0f, 1.0f);
const Vector4D AxisX4D(1.0f, 0.0f, 0.0f, 0.0f);
const Vector4D AxisY4D(0.0f, 1.0f, 0.0f, 0.0f);
const Vector4D AxisZ4D(0.0f, 0.0f, 1.0f, 0.0f);
const Vector4D AxisW4D(0.0f, 0.0f, 0.0f, 1.0f);
inline double  Dot(const Vector2D&, const Vector2D&);
inline double  Dot(const Vector3D&, const Vector3D&);
inline double  Dot(const Vector4D&, const Vector4D&);
// 只有三维向量才有叉积
inline Vector3D Cross(const Vector3D&, const Vector3D&);

inline bool IsParallel(const Vector3D&, const Vector3D&);
inline bool IsParallel(const Vector2D&, const Vector2D&);
inline bool IsVertical(const Vector3D&, const Vector3D&);
inline bool IsVertical(const Vector2D&, const Vector2D&);

inline Vector2D operator+(const Vector2D&, const Vector2D&);
inline Vector3D operator+(const Vector3D&, const Vector3D&);
inline Vector4D operator+(const Vector4D&, const Vector4D&);

inline Vector2D operator-(const Vector2D&, const Vector2D&);
inline Vector3D operator-(const Vector3D&, const Vector3D&);
inline Vector4D operator-(const Vector4D&, const Vector4D&);

inline Vector2D operator*(const float, const Vector2D&);
inline Vector2D operator*(const Vector2D&, const float);
inline Vector3D operator*(const float, const Vector3D&);
inline Vector3D operator*(const Vector3D&, const float);
inline Vector4D operator*(const float, const Vector4D&);
inline Vector4D operator*(const Vector4D&, const float);

inline Vector2D Zoom(const float, const Vector2D&);
inline Vector2D Zoom(const Vector2D&, const float);
inline Vector3D Zoom(const float, const Vector3D&);
inline Vector3D Zoom(const Vector3D&, const float);
inline Vector4D Zoom(const float, const Vector4D&);
inline Vector4D Zoom(const Vector4D&, const float);
}  // namespace ExCCCRender::Core::Math