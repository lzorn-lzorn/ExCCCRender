#pragma once
#include <cmath>
#include <limits>
#include "tools/static_for.hpp"
#include "vector_detail.hpp"

namespace ExCCCRender::Core::Math{
    struct Vector2D{
    public:
        explicit Vector2D(const float x,  const float y):
            vec_2(x, y) {}
        explicit Vector2D(){}
        ~Vector2D(){}
        Vector2D(const Vector2D& vec) = default;
        Vector2D(Vector2D&& vec) = default;
        Vector2D& operator=(const Vector2D& vec) = default;
        Vector2D& operator=(Vector2D&& vec) = default;
        bool operator==(const Vector2D&);
    public:
        Vector2D& SetX(const float x=0.0f) noexcept{
            return vec_2.p_coordinates[0] = x, *this;
        }
        Vector2D& SetY(const float y=0.0f) noexcept{
            return vec_2.p_coordinates[0] = y, *this;
        }
        Vector2D& SetXY(const float x=0.0f, const float y=0.0f) noexcept{
            vec_2.p_coordinates[0] = x;
            vec_2.p_coordinates[1] = y;
            return *this;
        }
        float X() const noexcept{
            return vec_2.p_coordinates[0];
        }
        float Y() const noexcept{
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
    public:
        Vector2D& Normalize() {
            return vec_2.normalize(), *this;
        }
        Vector2D& ProportionallyChange(const float ratio){
            return vec_2.proportionally_change(ratio), *this;
        }
    private:
        detail::vector_n<2> vec_2;
    };

    struct Vector3D{
    public:
        explicit Vector3D(const float x,  const float y, const float z):
            vec_3(x, y, z) {}
        explicit Vector3D(){}
        ~Vector3D(){}
        Vector3D(const Vector3D& vec) = default;
        Vector3D(Vector3D&& vec) = default;
        Vector3D& operator=(const Vector3D& vec) = default;
        Vector3D& operator=(Vector3D&& vec) = default;

        bool operator==(const Vector3D& vec) ;
    public:
        Vector3D& SetX(const float x){
            return vec_3.p_coordinates[0] = x, *this;
        }
        Vector3D& SetY(const float y){
            return vec_3.p_coordinates[1] = y, *this;
        }
        Vector3D& SetZ(const float z){
            return vec_3.p_coordinates[2] = z, *this;
        }
        Vector3D& SetXYZ(const float x, const float y, const float z){
            vec_3.p_coordinates[0] = x;
            vec_3.p_coordinates[1] = y;
            vec_3.p_coordinates[2] = z;
            return *this;
        }
        // @ 返回模的平方
        double SquareSum() const noexcept{
            return vec_3.square_sum();
        }

        double Length() const noexcept{
            return vec_3.length();
        }
        double Size() const noexcept{
            return vec_3.length();
        }

        double X() const noexcept{
            return vec_3.p_coordinates[0];
        }
        double Y() const noexcept{
            return vec_3.p_coordinates[1];
        }
        double Z() const noexcept{
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
    public:
        Vector3D& Normalize() {
            return vec_3.normalize(), (*this);
        }
    private:
        detail::vector_n<3> vec_3;
    };

    struct Vector4D{
    public:
        explicit Vector4D(const float x,  const float y, const float z, const float w):
            vec_4(x, y, z, w) {}
        explicit Vector4D(){}
        ~Vector4D(){}
        Vector4D(const Vector4D& vec) = default;
        Vector4D(Vector4D&& vec) = default;
        Vector4D& operator=(const Vector4D& vec) = default;
        Vector4D& operator=(Vector4D&& vec) = default;
        bool operator==(const Vector4D&);
    public:
        Vector4D& SetX(const float x=float{}) {

            return vec_4.p_coordinates[0] = x, *this;
        }
        Vector4D& SetY(const float y=float{}) {
            return vec_4.p_coordinates[1] = y, *this;
        }
        Vector4D& SetZ(const float z=float{}){
            return vec_4.p_coordinates[2] = z, *this;
        }
        Vector4D& SetW(const float w=float{}){
            return vec_4.p_coordinates[3] = w, *this;
        }
        Vector4D& SetXYZW(const float x=float{},
                     const float y=float{},
                     const float z=float{},
                     const float w=float{}){
            vec_4.p_coordinates[0] = x;
            vec_4.p_coordinates[1] = y;
            vec_4.p_coordinates[2] = z;
            vec_4.p_coordinates[3] = w;
            return *this;
        }
        // @ 返回模的平方
        double SquareSum() const noexcept{
            return vec_4.square_sum();
        }

        double Length() const noexcept{
            return vec_4.length();
        }
        double Size() const noexcept{
            return vec_4.length();
        }

        double X() const noexcept{
            return vec_4.p_coordinates[0];
        }
        double Y() const noexcept{
            return vec_4.p_coordinates[1];
        }
        double Z() const noexcept{
            return vec_4.p_coordinates[2];
        }
        double W() const noexcept{
            return vec_4.p_coordinates[3];
        }
        double X() noexcept{
            return vec_4.p_coordinates[0];
        }
        double Y() noexcept{
            return vec_4.p_coordinates[1];
        }
        double Z() noexcept{
            return vec_4.p_coordinates[2];
        }
        double W() noexcept{
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
    private:
        detail::vector_n<4> vec_4;
    };


};