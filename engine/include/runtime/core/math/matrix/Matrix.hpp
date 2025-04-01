#pragma once
#include "runtime/core/math/vector/Vector.hpp"
namespace ExCCCRender::Core::Math::Matrix{
/*
 *  以下是矩阵类的接口定义, 分成两个部分:
 *  1. 矩阵的接口部分
 *  2. 矩阵的细节实现部分
 *  但是关于矩阵的细节实现部分, 其本质上也是接口, 我选择来封装一个矩阵运算的库
 *  所以会 matrix_detail 来封装具体库的接口, 从而实现一个中间层
 *  即时之后要更换矩阵的具体后端, 也需要实现其接口, 而不影响后续的调用
 */
    struct Matrix2D{};
    struct Matrix3D{};
    struct Matrix4D{};

}
