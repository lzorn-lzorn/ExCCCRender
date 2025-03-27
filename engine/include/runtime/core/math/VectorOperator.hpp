#pragma once
#include <type_traits>
#include "Vector.hpp"
#include "pch.hpp"
#include "runtime/core/math/Vector.hpp"

namespace ExCCCRender::Tools::Math {
    template <Arithmetic T, Arithmetic U>
    bool IsParallel(const Vector3D<T>& v1, const Vector3D<U>& v2){
        return v1.IsParallelWith(v2);
    }
    template <Arithmetic T, Arithmetic U>
    bool IsParallel(const Vector2D<T>& v1, const Vector2D<U>& v2){
        return v1.IsParallelWith(v2);
    }

    template <Arithmetic T, Arithmetic U>
    bool IsVertical(const Vector3D<T>& v1, const Vector3D<U>& v2){
        return v1.IsVerticalWith(v2);
    }
    template <Arithmetic T, Arithmetic U>
    bool IsVertical(const Vector2D<T>& v1, const Vector2D<U>& v2){
        return v1.IsVerticalWith(v2);
    }

    template <Arithmetic T, Arithmetic U>
    auto Dot(const Vector3D<T>& v1, const Vector3D<U>& v2)
        -> std::common_type_t<T, U>{
        return v1.Dot(v2);
    }

    template <Arithmetic T, Arithmetic U>
    auto Dot(const Vector2D<T> v1, const Vector2D<U> v2)
        -> std::common_type_t<T, U>{
        return v1.Dot(v2);
    }

    template <Arithmetic T, Arithmetic U>
    auto Cross(const Vector3D<T>& v1, const Vector3D<U>& v2)
        -> Vector3D<std::common_type_t<T, U>>{
        return v1.Cross(v2);
    }

    template <Arithmetic T, Arithmetic U>
    auto Cross(const Vector2D<T>& v1, const Vector2D<U>& v2)
        -> Vector2D<std::common_type_t<T, U>>{
        return v1.Cross(v2);
    }
}