#pragma once
#include <type_traits>
#include "core/math/vector/Vector.hpp"

namespace ExCCCRender::Core::Math {

template <size_t N, size_t M>
struct Matrix {};

// 这里判断M>1
template <size_t N>
struct Matrix<N, N> {
    // * 获取该维度下的单位矩阵
    static Matrix<N, N> Identity() {
        Matrix<N, N> result;
        // Implementation would initialize diagonal elements to 1
        return result;
    }

    // * 求其行列式
    double Determinant() const;

    // * 获取逆矩阵
    Matrix<N, N>& Inverse() const;

    // * 转置
    Matrix<N, N>& Transpose() const;

    // * 判断其是否为对称矩阵
    bool IsSymmetric() const;

    // * 矩阵降低一维
    Matrix<N, N> ReduceDimensionality() {}

    // * 获取矩阵最右侧的常数列
    Matrix<N, 1> GetConstantBeta() const {}
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
