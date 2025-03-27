#pragma once
#include <exception>
#include <cmath>
#include <initializer_list>
#include <limits>
#include <cstdint>
#include <stdexcept>
#include <type_traits>
#include "tools/static_for.hpp"
/*
 * 以下是Vector(向量的定义)
 * 本质上Vector只有 2D, 3D, 4D
 * 所有的Vector的特化类型, 例如 RGB:Vector3D<uint8_t> 都需要拥有以下方法:
 *     ToVectorXD：转化至对应的VectorXD类型
 */

namespace ExCCCRender::Tools::Math{
    template <typename Ty>
    concept Arithmetic = std::is_arithmetic<Ty>::value;

    template <Arithmetic Ty>
    struct Vector2D{
    public:
        using inner_type = Ty;
    public:
        explicit Vector2D(const inner_type& x,  const inner_type& y):
            x(x), y(y) {}
        explicit Vector2D(){}
        ~Vector2D(){}
        Vector2D(const Vector2D& vec) = default;
        Vector2D(Vector2D&& vec) = default;
        Vector2D& operator=(const Vector2D& vec) = default;
        Vector2D& operator=(Vector2D&& vec) = default;
        template <typename OtherTy>
        bool operator==(const Vector2D<OtherTy>& vec) {
            using operator_type_ = std::common_type_t<OtherTy, inner_type>;
            auto epsilon =std::numeric_limits<operator_type_>::epsilon();
            if (std::abs(x-vec.X()) <= epsilon &&
                std::abs(y-vec.Y()) <= epsilon){
                return true;
            }
            return false;
        }
        inner_type operator[](const size_t& i) const{
            if (i == 0) return x;
            if (i == 1) return y;
            throw std::out_of_range("Index out of range");
        }
    public:
        Vector2D& SetX(const inner_type& x=inner_type{}) noexcept{
            this->x = x;
            return *this;
        }
        Vector2D& SetY(const inner_type& y=inner_type{}) noexcept{
            this->y = y;
            return *this;
        }
        void SetXY(const inner_type& x=inner_type{}, const inner_type& y=inner_type{}) noexcept{
            this->x = x;
            this->y = y;
        }
        inner_type GetX() const noexcept{
            return x;
        }
        inner_type GetY() const noexcept{
            return y;
        }
        inner_type X() const noexcept{
            return x;
        }
        inner_type Y() const noexcept{
            return y;
        }

        inner_type LengthSquare() const noexcept{
            return square_();
        }
        inner_type SizeSquare() const noexcept{
            return square_();
        }
        double GetLength() const noexcept{
            return length_();
        }
        double Length() const noexcept{
            return length_();
        }
        double Size() const noexcept{
            return length_();
        }
    public:
        bool IsZeroVector() const noexcept{
            auto inner_value_ = inner_type{};
            return this->x == inner_value_ && this->y == inner_value_;
        }
        bool IsUnitVector() const noexcept{
            // * 坐标轴向量直接返回true
            if(IsAxis()){
                return true;
            }
            return square_() == (inner_type)1;
        }
        bool IsAxis() const noexcept{
            auto inner_value_ = inner_type{};
            return (this->x == (inner_type)1 && this->y == inner_value_) ||
                (this->x == inner_value_ && this->y == (inner_type)1) ;
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
            if (IsUnitVector() || square_() == 1){
                return *this;
            }
            auto size = Size();
            x /= size;
            y /= size;
            return *this;
        }
        template <typename OtherTy>
        auto Dot(const Vector2D<OtherTy>& other) const -> std::common_type_t<inner_type, OtherTy>{
            using result_type_ = std::common_type_t<inner_type, OtherTy>;
            return static_cast<result_type_>(x) * static_cast<result_type_>(other.X()) +
               static_cast<result_type_>(y) * static_cast<result_type_>(other.Y());
        }
    private:
        double length_() const noexcept{
            if (IsUnitVector()){
                return 1.0;
            }
            return std::sqrt(square_());
        }
        inner_type square_() const noexcept{
            return x*x+y*y;
        }
    private:
        inner_type x{}, y{};
    };
    template <Arithmetic Ty>
    struct Vector3D{
    public:
        using inner_type = Ty;
    public:
        explicit Vector3D(const inner_type& x,  const inner_type& y, const inner_type& z):
            x(x), y(y), z(z) {}
        explicit Vector3D(){}
        ~Vector3D(){}
        Vector3D(const Vector3D& vec) = default;
        Vector3D(Vector3D&& vec) = default;
        Vector3D& operator=(const Vector3D& vec) = default;
        Vector3D& operator=(Vector3D&& vec) = default;
        template <typename OtherTy>
        bool operator==(const Vector3D<OtherTy>& vec) {
            using operator_type_ = std::common_type_t<OtherTy, inner_type>;
            auto epsilon =std::numeric_limits<operator_type_>::epsilon();
            if (std::abs(x-vec.X()) <= epsilon &&
                std::abs(y-vec.Y()) <= epsilon &&
                std::abs(z-vec.Z()) <= epsilon){
                return true;
            }
            return false;
        }
    public:
        Vector2D<inner_type> ToVector2D() const {
            return Vector2D<inner_type>(this->x, this->y);
        }
        Vector3D& SetX(const inner_type& x=inner_type{}) {
            this->x = x;
            return *this;
        }
        Vector3D& SetY(const inner_type& y=inner_type{}) {
            this->y = y;
            return *this;
        }
        Vector3D& SetZ(const inner_type& z=inner_type{}){
            this->z = z;
            return *this;
        }
        void SetXYZ(const inner_type& x=inner_type{},
                    const inner_type& y=inner_type{},
                    const inner_type& z=inner_type{}){
            this->x = x;
            this->y = y;
            this->z = z;
        }
        inner_type LengthSquare() const noexcept{
            return square_();
        }
        inner_type SizeSquare() const noexcept{
            return square_();
        }
        double GetLength() const noexcept{
            return length_();
        }
        double Length() const noexcept{
            return length_();
        }
        double Size() const noexcept{
            return length_();
        }
        inner_type GetX() const noexcept{
            return x;
        }
        inner_type GetY() const noexcept{
            return y;
        }
        inner_type GetZ() const noexcept{
            return z;
        }
        inner_type X() const noexcept{
            return x;
        }
        inner_type Y() const noexcept{
            return y;
        }
        inner_type Z() const noexcept{
            return z;
        }
        inner_type operator[](const size_t& i) const{
            if (i == 0) return x;
            if (i == 1) return y;
            if (i == 2) return z;
            throw std::out_of_range("Index out of range");
        }

    public:
    // ! 谓词方法
        bool IsZeroVector() const noexcept{
            auto inner_value_ = inner_type{};
            return this->x == inner_value_ && this->y == inner_value_ && this->z == inner_value_;
        }
        bool IsUnitVector() const noexcept{
            // * 坐标轴向量直接返回true
            if(IsAxis()){
                return true;
            }
            return square_() == (inner_type)1;
        }
        bool IsAxis() const noexcept{
            auto inner_value_ = inner_type{};
            return (this->x == (inner_type)1 && this->y == inner_value_, this->z == inner_value_) ||
                (this->x == inner_value_ && this->y == (inner_type)1, this->z == inner_value_) ||
                 (this->x == inner_value_ && this->y == inner_value_, this->z == (inner_type)1);
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
            if (IsUnitVector() || square_() == 1){
                return *this;
            }
            auto size = Size();
            x /= size;
            y /= size;
            z /= size;
            return *this;
        }
        template <typename OtherTy>
        auto Dot(const Vector3D<OtherTy>& other) const -> std::common_type_t<inner_type, OtherTy>{
            return x * other.X() + y * other.Y() + z * other.Z();
        }
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
            result_inner_type x = y * other.Z() - z * other.Y();
            result_inner_type y = x * other.Z() - z * other.X();
            result_inner_type z = x * other.Y() - y * other.X();
            return Vector3D<result_inner_type>(x, y, z);
        }
    private:
        double length_() const noexcept{
            if (IsUnitVector()){
                return 1.0;
            }
            return std::sqrt(square_());
        }
        inner_type square_() const noexcept{
            return x*x+y*y+z*z;
        }
    private:
        inner_type x{}, y{}, z{};
    };

    namespace detail {
        template <Arithmetic Ty, size_t N>
        struct vector_n{
            // * 防止溢出类型
            using ResultType = std::conditional_t<std::is_integral_v<Ty>,
                    std::conditional_t<(sizeof(Ty) <= sizeof(int16_t)),
                        int16_t,
                        std::conditional_t<(sizeof(Ty) == sizeof(int32_t)),
                            int32_t,
                            std::conditional_t<(sizeof(Ty) == sizeof(int64_t)),
                                int64_t,
                                int64_t // int64 为最高
                            >
                        >
                    >,
                    std::conditional_t<std::is_floating_point_v<Ty>,
                        long double,
                        Ty
                    >
                >;
        public:
            explicit vector_n(std::initializer_list<Ty> list){
                p_coordinates = std::array<Ty, N>(list.begin(), list.end());
            }
            vector_n(const vector_n& other){

            }
            vector_n(vector_n&& other){}
            vector_n& operator=(const vector_n& other){}
            vector_n& operator=(vector_n&& other){}
            bool operator==(const vector_n& other){}
        public:
            bool is_zero_vector() const noexcept{
                bool ret = true;
                auto epsilon = std::numeric_limits<Ty>::epsilon();
                static_for<0, N>([&](size_t i){
                    if constexpr (p_coordinates[i] <= epsilon){
                        ret = false;
                    }
                });
                return ret;
            }
            bool is_unit_vector() const noexcept{}
            bool is_axis() const noexcept{
                size_t count = 0;
                static_for<N>([&](auto i) {
                    if constexpr(p_coordinates[i] == 1) {
                        ++count;
                    } else if (p_coordinates[i] != 0) {
                        count = 2; // 直接标记为不符合条件
                    }
                });
                return count == 1;
            }
            bool is_parallel_with(const vector_n& vec){}
            bool is_vertical_with(const vector_n& vec){}
        public:
            void normalize() {}
            auto dot(const vector_n& vec){
                ResultType res{};
                static_for<N>([&](size_t i){
                    res += p_coordinates[i] * vec.p_coordinates[i];
                });
            }
            vector_n<Ty, N> cross(const vector_n& vec){}
            double length() const noexcept{
                if (is_unit_vector()){
                    return 1.0;
                }
                return std::sqrt(square());
            }

            // * 返回 x*x+y*y+z*z
            auto square() const noexcept{
                ResultType res = 0;
                static_for<N>([&](size_t i){
                    res += p_coordinates[i] * p_coordinates[i];
                });
                return res;
            }
        public:
            std::array<Ty, N> p_coordinates;
        };
    }
};