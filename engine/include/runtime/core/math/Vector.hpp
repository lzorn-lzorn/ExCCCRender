#pragma once
#include <exception>
#include <cmath>
#include <initializer_list>
#include <limits>
#include <cstdint>
#include <stdexcept>
#include <type_traits>
#include "tools/static_for.hpp"
#include "pch.hpp"
#include "vector_detail.hpp"
/*
 * 以下是Vector(向量的定义)
 * 本质上Vector只有 2D, 3D, 4D
 * 所有的Vector的特化类型, 例如 RGB:Vector3D<uint8_t> 都需要拥有以下方法:
 *     ToVectorXD：转化至对应的VectorXD类型
 */

namespace ExCCCRender::Tools::Math{
    template <Arithmetic Ty>
    struct Vector2D{
    public:
        using inner_type = Ty;
    public:
        explicit Vector2D(const inner_type& x,  const inner_type& y):
            vec_2(x, y) {}
        explicit Vector2D(){}
        ~Vector2D(){}
        Vector2D(const Vector2D& vec) = default;
        Vector2D(Vector2D&& vec) = default;
        Vector2D& operator=(const Vector2D& vec) = default;
        Vector2D& operator=(Vector2D&& vec) = default;
        template <typename OtherTy>
        bool operator==(const Vector2D<OtherTy>& vec) {
            return vec_2.p_coordinates[0] == vec.X() &&
                vec_2.p_coordinates[1] == vec.Y();
        }
    public:
        Vector2D& SetX(const inner_type& x=inner_type{}) noexcept{
            vec_2.p_coordinates[0] = x;
            return *this;
        }
        Vector2D& SetY(const inner_type& y=inner_type{}) noexcept{
            vec_2.p_coordinates[1] = y;
            return *this;
        }
        void SetXY(const inner_type& x=inner_type{}, const inner_type& y=inner_type{}) noexcept{
            vec_2.p_coordinates[0]= x;
            vec_2.p_coordinates[1] = y;
        }
        inner_type X() const noexcept{
            return vec_2.p_coordinates[0];
        }
        inner_type Y() const noexcept{
            return vec_2.p_coordinates[1];
        }

        auto SquareSum() const noexcept{
            return vec_2.square_sum();
        }
        double Length() const noexcept{
            return vec_2.length();
        }
        double Size() const noexcept{
            return vec_2.length();
        }
    public:
        bool IsZeroVector() const noexcept{
            return vec_2.is_zero_vector();
        }
        bool IsUnitVector() const noexcept{
            return vec_2.is_unit_vector();
        }
        bool IsAxis() const noexcept{
            return vec_2.is_axis();
        }
        template <typename OtherTy>
        bool IsParallelWith(const Vector2D<OtherTy>& other) const {
            using operator_type_ = std::common_type_t<OtherTy, inner_type>;
            auto epsilon = std::numeric_limits<operator_type_>::epsilon();
            return (other.X() * y - other.Y() * x) <= epsilon;
        }
        template <typename OtherTy>
        bool IsVerticalWith(const Vector2D<OtherTy>& other) const {
            using operator_type_ = std::common_type_t<OtherTy, inner_type>;
            auto vec_ = Dot<OtherTy>(other);
            auto epsilon = std::numeric_limits<operator_type_>::epsilon();
            return vec_ <= epsilon;
        }
    public:
        Vector2D& Normalize() {
            vec_2.normalize();
            return *this;
        }
        template <typename OtherTy>
        auto Dot(const Vector2D<OtherTy>& other) const {
            return vec_2.dot(other);
        }
    private:
        double length_() const noexcept{
            if (IsUnitVector()){
                return 1.0;
            }
            return std::sqrt(square_());
        }
        inner_type square_() const noexcept{
            return vec_2.p_coordinates[0]*vec_2.p_coordinates[0]
             + vec_2.p_coordinates[1]*vec_2.p_coordinates[1];
        }
    private:
        inner_type x{}, y{};
        detail::vector_n<Ty, 2> vec_2;
    };
    template <Arithmetic Ty>
    struct Vector3D{
    public:
        using inner_type = Ty;
    public:
        explicit Vector3D(const inner_type& x,  const inner_type& y, const inner_type& z):
            vec_3(x, y, z) {}
        explicit Vector3D(){}
        ~Vector3D(){}
        Vector3D(const Vector3D& vec) = default;
        Vector3D(Vector3D&& vec) = default;
        Vector3D& operator=(const Vector3D& vec) = default;
        Vector3D& operator=(Vector3D&& vec) = default;
        template <typename OtherTy>
        bool operator==(const Vector3D<OtherTy>& vec) {
            return vec_3.p_coordinates[0] == vec.X()
                && vec_3.p_coordinates[1] == vec.Y()
                && vec_3.p_coordinates[2] == vec.Z();
        }
    public:
        Vector2D<inner_type> ToVector2D() const {
            return Vector2D<inner_type>(vec_3.p_coordinates[0], vec_3.p_coordinates[1]);
        }
        Vector3D& SetX(const inner_type& x=inner_type{}) {
            vec_3.p_coordinates[0] = x;
            return *this;
        }
        Vector3D& SetY(const inner_type& y=inner_type{}) {
            vec_3.p_coordinates[1] = y;
            return *this;
        }
        Vector3D& SetZ(const inner_type& z=inner_type{}){
            vec_3.p_coordinates[2] = z;
            return *this;
        }
        void SetXYZ(const inner_type& x=inner_type{},
                    const inner_type& y=inner_type{},
                    const inner_type& z=inner_type{}){
            vec_3.p_coordinates[0] = x;
            vec_3.p_coordinates[1] = y;
            vec_3.p_coordinates[2] = z;
        }
        // @ 返回模的平方
        auto SquareSum() const noexcept{
            return vec_3.square_sum();
        }

        auto Length() const noexcept{
            return vec_3.length();
        }
        auto Size() const noexcept{
            return vec_3.length();
        }

        auto X() const noexcept{
            return vec_3.p_coordinates[0];
        }
        auto Y() const noexcept{
            return vec_3.p_coordinates[1];
        }
        auto Z() const noexcept{
            return vec_3.p_coordinates[2];
        }

    public:
    // ! 谓词方法
        bool IsZeroVector() const noexcept{
            return vec_3.is_zero_vector();
        }
        bool IsUnitVector() const noexcept{
            return vec_3.is_unit_vector();
        }
        bool IsAxis() const noexcept{
           return vec_3.is_axis();
        }
        template <typename OtherTy>
        bool IsParallelWith(const Vector3D<OtherTy>& other) const {
            using operator_type_ = std::common_type_t<OtherTy, inner_type>;
            Vector3D<operator_type_> tmp_vec_ = Cross<OtherTy>(other);
            auto epsilon = std::numeric_limits<operator_type_>::epsilon();
            return tmp_vec_.X() <= epsilon && tmp_vec_.Y() <= epsilon && tmp_vec_.Z() <= epsilon;
        }
        template <typename OtherTy>
        bool IsVerticalWith(const Vector3D<OtherTy>& other) const {
            using operator_type_ = std::common_type_t<OtherTy, inner_type>;
            auto vec_ = Dot<OtherTy>(other);
            auto epsilon = std::numeric_limits<operator_type_>::epsilon();
            return vec_ <= epsilon;
        }

    public:
        Vector3D& Normalize() {
            vec_3.normalize();
        }
        template <typename OtherTy>
        auto Dot(const Vector3D<OtherTy>& other) const -> std::common_type_t<inner_type, OtherTy>{
            return vec_3.p_coordinates[0] * other.X()
                 + vec_3.p_coordinates[1] * other.Y()
                 + vec_3.p_coordinates[2] * other.Z();
        }
        // note: 只有三维向量有叉积
        template <typename OtherTy>
        auto Cross(const Vector3D<OtherTy>& other) const
          -> Vector3D<std::common_type_t<inner_type, OtherTy>>{
            using result_inner_type = std::common_type_t<inner_type, OtherTy>;
            if (other == *this){
                return Vector3D<inner_type>(0, 0, 0);
            }
            if (other.IsZeroVector()){
                auto inner_value_ = inner_type{};
                return Vector3D<OtherTy>(inner_value_, inner_value_, inner_value_);
            }
            result_inner_type x = vec_3.p_coordinates[1] * other.Z() - vec_3.p_coordinates[2] * other.Y();
            result_inner_type y = vec_3.p_coordinates[0] * other.Z() - vec_3.p_coordinates[2] * other.X();
            result_inner_type z = vec_3.p_coordinates[0] * other.Y() - vec_3.p_coordinates[1] * other.X();
            return Vector3D<result_inner_type>(x, y, z);
        }
    private:
        detail::vector_n<Ty, 3> vec_3;
    };

    template <Arithmetic Ty>
    struct Vector4D{
    public:
        using inner_type = Ty;
    public:
        explicit Vector4D(const inner_type& x,  const inner_type& y, const inner_type& z, const inner_type& w):
            vec_4(x, y, z, w) {}
        explicit Vector4D(){}
        ~Vector4D(){}
        Vector4D(const Vector4D& vec) = default;
        Vector4D(Vector4D&& vec) = default;
        Vector4D& operator=(const Vector4D& vec) = default;
        Vector4D& operator=(Vector4D&& vec) = default;
        template <typename OtherTy>
        bool operator==(const Vector4D<OtherTy>& vec) {
            return vec_4.p_coordinates[0] == vec.X()
                && vec_4.p_coordinates[1] == vec.Y()
                && vec_4.p_coordinates[2] == vec.Z()
                && vec_4.p_coordinates[3] == vec.W();
        }
    public:
        Vector2D<inner_type> ToVector3D() const {
            return Vector2D<inner_type>(vec_4.p_coordinates[0], vec_4.p_coordinates[1], vec_4.p_coordinates[2]);
        }
        Vector4D& SetX(const inner_type& x=inner_type{}) {
            vec_4.p_coordinates[0] = x;
            return *this;
        }
        Vector4D& SetY(const inner_type& y=inner_type{}) {
            vec_4.p_coordinates[1] = y;
            return *this;
        }
        Vector4D& SetZ(const inner_type& z=inner_type{}){
            vec_4.p_coordinates[2] = z;
            return *this;
        }
        Vector4D& SetW(const inner_type& w=inner_type{}){
            vec_4.p_coordinates[3] = w;
            return *this;
        }
        void SetXYZW(const inner_type& x=inner_type{},
                     const inner_type& y=inner_type{},
                     const inner_type& z=inner_type{},
                     const inner_type& w=inner_type{}){
            vec_4.p_coordinates[0] = x;
            vec_4.p_coordinates[1] = y;
            vec_4.p_coordinates[2] = z;
            vec_4.p_coordinates[3] = w;
        }
        // @ 返回模的平方
        auto SquareSum() const noexcept{
            return vec_4.square_sum();
        }

        auto Length() const noexcept{
            return vec_4.length();
        }
        auto Size() const noexcept{
            return vec_4.length();
        }

        auto X() const noexcept{
            return vec_4.p_coordinates[0];
        }
        auto Y() const noexcept{
            return vec_4.p_coordinates[1];
        }
        auto Z() const noexcept{
            return vec_4.p_coordinates[2];
        }
        auto W() const noexcept{
            return vec_4.p_coordinates[3];
        }
    public:
    // ! 谓词方法
        bool IsZeroVector() const noexcept{
            return vec_4.is_zero_vector();
        }
        bool IsUnitVector() const noexcept{
            return vec_4.is_unit_vector();
        }
        bool IsAxis() const noexcept{
           return vec_4.is_axis();
        }

    public:
        Vector4D& Normalize() {
            vec_4.normalize();
        }
        template <typename OtherTy>
        auto Dot(const Vector4D<OtherTy>& other) {
            return vec_4.p_coordinates[0] * other.X()
                 + vec_4.p_coordinates[1] * other.Y()
                 + vec_4.p_coordinates[2] * other.Z()
                 + vec_4.p_coordinates[3] * other.W();
        }
    private:
        detail::vector_n<Ty, 4> vec_4;
    };


};