#pragma once
#include <type_traits>
#include "core/math/vector/Vector.hpp"

namespace ExCCCRender::Core::Math {

template <size_t N, size_t M>
struct Matrix {};

// 这里判断M>1
template <size_t N, size_t M>
    requires(M > 1)
struct Matrix<N, M> {
    // Square matrix specialization

    // Identity matrix creation
    static Matrix<N, N> Identity() {
        Matrix<N, N> result;
        // Implementation would initialize diagonal elements to 1
        return result;
    }

    // Determinant calculation (declaration)
    double Determinant() const;

    // Inverse matrix calculation (declaration)
    Matrix<N, N> Inverse() const;

    // Transpose (for square matrices, size doesn't change)
    Matrix<N, N> Transpose() const;

    // Check if matrix is symmetric
    bool IsSymmetric() const;
};

// 这里判断M==1，使用类特化而不是别名模板
template <size_t N, size_t M>
    requires(M == 1)
struct Matrix<N, M> {
    // 封装一个VectorXD
    VectorXD<N> data;

    // 转换构造函数
    Matrix(const VectorXD<N>& vec) : data(vec) {
    }

    // 默认构造函数
    Matrix() = default;

    // 转换操作符
    operator VectorXD<N>&() {
        return data;
    }

    operator const VectorXD<N>&() const {
        return data;
    }
};
}  // namespace ExCCCRender::Core::Math
