#pragma once
#include <cmath>
#include <limits>
#include "tools/static_for.hpp"
#include "vector_detail.hpp"

namespace ExCCCRender::Core::Math {
using namespace ExCCCRender::Core::Math::detail;
struct Vector2D: public VectorBase<2> {
public:
    constexpr static size_t Dimension = 2;
public:
    explicit Vector2D(const float x, const float y) : VectorBase(x, y) {
    }

    explicit Vector2D() : VectorBase(0.0f, 0.0f) {
    }

    ~Vector2D() {
    }

    Vector2D(const Vector2D& vec)            = default;
    Vector2D(Vector2D&& vec)                 = default;
    Vector2D& operator=(const Vector2D& vec) = default;
    Vector2D& operator=(Vector2D&& vec)      = default;

    bool operator==(const Vector2D& vec) const{
        return VectorBase<2>::operator==(vec);
    }

    Vector2D& operator+(const Vector2D& other) {
        return VectorBase<2>::operator+=(other), *this;
    }

    Vector2D& operator-(const Vector2D& other) {
        return VectorBase<2>::operator-=(other), *this;
    }

    Vector2D& operator+=(const Vector2D& other) {
        return VectorBase<2>::operator+=(other), *this;
    }

    Vector2D& operator-=(const Vector2D& other) {
        return VectorBase<2>::operator-=(other), *this;
    }

    Vector2D& operator+=(const float num) {
        return VectorBase<2>::operator+=(num), *this;
    }

    Vector2D& operator-=(const float num) {
        return VectorBase<2>::operator-=(num), *this;
    }

public:
    Vector2D& SetX(const float x = 0.0f) noexcept {
        return coordinates[0] = x, *this;
    }

    Vector2D& SetY(const float y = 0.0f) noexcept {
        return coordinates[1] = y, *this;
    }

    Vector2D& SetXY(const float x = 0.0f, const float y = 0.0f) noexcept {
        coordinates[0] = x;
        coordinates[1] = y;
        return *this;
    }

    float X() const noexcept {
        return coordinates[0];
    }

    float Y() const noexcept {
        return coordinates[1];
    }

    double SquareSum() const noexcept {
        return square_sum();
    }

    double Length() const noexcept {
        return length();
    }

    double Size() const noexcept {
        return length();
    }

public:
    bool IsZeroVector() const noexcept {
        return is_zero_vector();
    }

    bool IsUnitVector() const noexcept {
        return is_unit_vector();
    }

    bool IsAxis() const noexcept {
        return is_axis();
    }

public:
    double Dot(const Vector2D& other){
        return Vector2D::dot(other);
    }
    double Dot(const Vector2D& other) const {
        return Vector2D::dot(other);
    }
    Vector2D& Normalize() {
        return normalize(), *this;
    }

    Vector2D& Zoom(const float ratio) {
        return proportionally_change(ratio), *this;
    }

};


struct Vector3D: public VectorBase<3>{
public:
    constexpr static size_t Dimension = 3;
public:
    explicit Vector3D(const float x, const float y, const float z) : VectorBase<3>(x, y, z) {
    }

    explicit Vector3D() : VectorBase<3>(0.0f, 0.0f, 0.0f) {
    }

    ~Vector3D() {
    }

    Vector3D(const Vector3D& vec)            = default;
    Vector3D(Vector3D&& vec)                 = default;
    Vector3D& operator=(const Vector3D& vec) = default;
    Vector3D& operator=(Vector3D&& vec)      = default;

    bool operator==(const Vector3D& vec) const{
        return VectorBase<3>::operator==(vec);
    }

    Vector3D& operator+(const Vector3D& other){
        return operator+=(other), *this;
    }

    Vector3D& operator-(const Vector3D& other){
        return operator-=(other);
    }
    Vector3D& operator+=(const Vector3D& other) {
        return VectorBase<3>::operator+=(other), *this;
    }

    Vector3D& operator-=(const Vector3D& other) {
        return VectorBase<3>::operator-=(other), *this;
    }

    Vector3D& operator+=(const float num) {
        return VectorBase<3>::operator+=(num), *this;
    }

    Vector3D& operator-=(const float num) {
        return VectorBase<3>::operator-=(num), *this;
    }

public:
    Vector3D& SetX(const float x) {
        return coordinates[0] = x, *this;
    }

    Vector3D& SetY(const float y) {
        return coordinates[1] = y, *this;
    }

    Vector3D& SetZ(const float z) {
        return coordinates[2] = z, *this;
    }

    Vector3D& SetXYZ(const float x, const float y, const float z) {
        coordinates[0] = x;
        coordinates[1] = y;
        coordinates[2] = z;
        return *this;
    }

    double X() const noexcept {
        return coordinates[0];
    }

    double Y() const noexcept {
        return coordinates[1];
    }

    double Z() const noexcept {
        return coordinates[2];
    }

    double SquareSum() const noexcept {
        return square_sum();
    }

    double Length() const noexcept {
        return length();
    }

    double Size() const noexcept {
        return length();
    }

    double Dot(const Vector3D& other){
        return Vector3D::dot(other);
    }
    double Dot(const Vector3D& other) const {
        return Vector3D::dot(other);
    }

public:
    bool IsZeroVector() const noexcept {
        return is_zero_vector();
    }

    bool IsUnitVector() const noexcept {
        return is_unit_vector();
    }

    bool IsAxis() const noexcept {
        return is_axis();
    }
public:
    Vector3D& Normalize() {
        return normalize(), (*this);
    }
    Vector3D& Zoom(const float ratio) {
        return proportionally_change(ratio), *this;
    }
};

struct Vector4D: public VectorBase<4>{
public:
    constexpr static size_t Dimension = 4;
public:
    explicit Vector4D(const float x, const float y, const float z, const float w) : VectorBase<4>(x, y, z, w) {
    }

    explicit Vector4D() : VectorBase<4>(0.0f, 0.0f, 0.0f, 0.0f) {
    }

    ~Vector4D() {
    }

    Vector4D(const Vector4D& vec)            = default;
    Vector4D(Vector4D&& vec)                 = default;
    Vector4D& operator=(const Vector4D& vec) = default;
    Vector4D& operator=(Vector4D&& vec)      = default;

    bool operator==(const Vector4D& vec) const{
        return VectorBase<4>::operator==(vec);
    }

    Vector4D& operator+(const Vector4D& other) {
        return Vector4D::operator+=(other), *this;
    }

    Vector4D& operator-(const Vector4D& other) {
        return Vector4D::operator-=(other), *this;
    }

    Vector4D& operator+=(const Vector4D& other) {
        return Vector4D::operator+=(other), *this;
    }

    Vector4D& operator-=(const Vector4D& other) {
        return Vector4D::operator-=(other), *this;
    }

    Vector4D& operator+=(const float num) {
        return VectorBase::operator+=(num), *this;
    }

    Vector4D& operator-=(const float num) {
        return VectorBase::operator+=(num), *this;
    }

public:
    Vector4D& SetX(const float x = float{}) {
        return coordinates[0] = x, *this;
    }

    Vector4D& SetY(const float y = float{}) {
        return coordinates[1] = y, *this;
    }

    Vector4D& SetZ(const float z = float{}) {
        return coordinates[2] = z, *this;
    }

    Vector4D& SetW(const float w = float{}) {
        return coordinates[3] = w, *this;
    }

    Vector4D& SetXYZW(const float x = float{},
                      const float y = float{},
                      const float z = float{},
                      const float w = float{}) {
        coordinates[0] = x;
        coordinates[1] = y;
        coordinates[2] = z;
        coordinates[3] = w;
        return *this;
    }
    double X() const noexcept {
        return coordinates[0];
    }

    double Y() const noexcept {
        return coordinates[1];
    }

    double Z() const noexcept {
        return coordinates[2];
    }

    double W() const noexcept {
        return coordinates[3];
    }

    double X() noexcept {
        return coordinates[0];
    }

    double Y() noexcept {
        return coordinates[1];
    }

    double Z() noexcept {
        return coordinates[2];
    }

    double W() noexcept {
        return coordinates[3];
    }
    double SquareSum() const noexcept {
        return square_sum();
    }

    double Length() const noexcept {
        return length();
    }

    double Size() const noexcept {
        return length();
    }

public:

    bool IsZeroVector() const noexcept {
        return is_zero_vector();
    }

    bool IsUnitVector() const noexcept {
        return is_unit_vector();
    }

    bool IsAxis() const noexcept {
        return is_axis();
    }

public:
    double Dot(const Vector4D& other){
        return Vector4D::dot(other);
    }
    double Dot(const Vector4D& other) const {
        return Vector4D::dot(other);
    }
    Vector4D& Normalize() {
        return normalize(), *this;
    }
    Vector4D& Zoom(const float ratio) {
        return proportionally_change(ratio), *this;
    }
};

};  // namespace ExCCCRender::Core::Math