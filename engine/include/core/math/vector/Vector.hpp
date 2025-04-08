#pragma once
#include <cmath>
#include <limits>
#include "tools/static_for.hpp"
#include "VectorDetail.hpp"


namespace ExCCCRender::Core::Math {
using namespace ExCCCRender::Core::Math::detail;

struct Vector2D : public VectorBase<float, 2> {
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

    bool operator==(const Vector2D& vec) const {
        return VectorBase<float, 2>::operator==(vec);
    }

    Vector2D& operator+(const Vector2D& other) {
        return VectorBase<float, 2>::operator+=(other), *this;
    }

    Vector2D& operator-(const Vector2D& other) {
        return VectorBase<float, 2>::operator-=(other), *this;
    }

    Vector2D& operator+=(const Vector2D& other) {
        return VectorBase<float, 2>::operator+=(other), *this;
    }

    Vector2D& operator-=(const Vector2D& other) {
        return VectorBase<float, 2>::operator-=(other), *this;
    }

    Vector2D& operator+=(const float num) {
        return VectorBase<float, 2>::operator+=(num), *this;
    }

    Vector2D& operator-=(const float num) {
        return VectorBase<float, 2>::operator-=(num), *this;
    }

    float operator[](const size_t index) {
        return coordinates[index];
    }

    float operator[](const size_t index) const {
        return coordinates[index];
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
    double Dot(const Vector2D& other) {
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

struct Vector3D : public VectorBase<float, 3> {
public:
    constexpr static size_t Dimension = 3;

public:
    explicit Vector3D(const float x, const float y, const float z) : VectorBase<float, 3>(x, y, z) {
    }

    explicit Vector3D() : VectorBase<float, 3>(0.0f, 0.0f, 0.0f) {
    }

    ~Vector3D() {
    }

    Vector3D(const Vector3D& vec){
        this->coordinates = vec.coordinates;
    }
    Vector3D(Vector3D&& vec){
        if (this == &vec) {
            return;
        }
        this->coordinates.swap(vec.coordinates);
        std::fill(vec.coordinates.begin(), vec.coordinates.end(), 0.0f);
    }
    Vector3D& operator=(const Vector3D& vec) {
        this->coordinates = vec.coordinates;
        return *this;
    }
    Vector3D& operator=(Vector3D&& vec) {
        if (this == &vec) {
            return *this;
        }
        this->coordinates.swap(vec.coordinates);
        std::fill(vec.coordinates.begin(), vec.coordinates.end(), 0.0f);
        return *this;
    }


    bool operator==(const Vector3D& vec) const {
        return VectorBase<float, 3>::operator==(vec);
    }

    Vector3D& operator+(const Vector3D& other) {
        return operator+=(other), *this;
    }

    Vector3D& operator-(const Vector3D& other) {
        return operator-=(other);
    }

    Vector3D& operator+=(const Vector3D& other) {
        return VectorBase<float, 3>::operator+=(other), *this;
    }

    Vector3D& operator-=(const Vector3D& other) {
        return VectorBase<float, 3>::operator-=(other), *this;
    }

    Vector3D& operator+=(const float num) {
        return VectorBase<float, 3>::operator+=(num), *this;
    }

    Vector3D& operator-=(const float num) {
        return VectorBase<float, 3>::operator-=(num), *this;
    }
    float operator[](const size_t index) {
        return coordinates[index];
    }
    float operator[](const size_t index) const {
        return coordinates[index];
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

    double Dot(const Vector3D& other) {
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

struct Vector4D : public VectorBase<float, 4> {
public:
    constexpr static size_t Dimension = 4;

public:
    explicit Vector4D(const float x, const float y, const float z, const float w) : VectorBase<float, 4>(x, y, z, w) {
    }

    explicit Vector4D() : VectorBase<float, 4>(0.0f, 0.0f, 0.0f, 0.0f) {
    }

    ~Vector4D() {
    }

    Vector4D(const Vector4D& vec)            = default;
    Vector4D(Vector4D&& vec)                 = default;
    Vector4D& operator=(const Vector4D& vec) = default;
    Vector4D& operator=(Vector4D&& vec)      = default;

    bool operator==(const Vector4D& vec) const {
        return VectorBase<float, 4>::operator==(vec);
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

    float operator[](const size_t index) {
        return coordinates[index];
    }
    float operator[](const size_t index) const {
        return coordinates[index];
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
    double Dot(const Vector4D& other) {
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

template<size_t N>
struct VectorXD : public VectorBase<float, N> {};

static const Vector2D ZeroVector2D(0.0f, 0.0f);
static const Vector3D ZeroVector3D(0.0f, 0.0f, 0.0f);
static const Vector4D ZeroVector4D(0.0f, 0.0f, 0.0f, 0.0f);
static const Vector2D AxisX2D(1.0f, 0.0f);
static const Vector2D AxisY2D(0.0f, 1.0f);
static const Vector3D AxisX3D(1.0f, 0.0f, 0.0f);
static const Vector3D AxisY3D(0.0f, 1.0f, 0.0f);
static const Vector3D AxisZ3D(0.0f, 0.0f, 1.0f);
static const Vector4D AxisX4D(1.0f, 0.0f, 0.0f, 0.0f);
static const Vector4D AxisY4D(0.0f, 1.0f, 0.0f, 0.0f);
static const Vector4D AxisZ4D(0.0f, 0.0f, 1.0f, 0.0f);
static const Vector4D AxisW4D(0.0f, 0.0f, 0.0f, 1.0f);

inline double Dot(const Vector2D& v1, const Vector2D& v2) {
    return v1.Dot(v2);
}

inline double Dot(const Vector3D& v1, const Vector3D& v2) {
    return v1.Dot(v2);
}

inline double Dot(const Vector4D& v1, const Vector4D& v2) {
    return v1.Dot(v2);
}

inline Vector3D Cross(const Vector3D& v1, const Vector3D& v2) {
    return Vector3D(v1.Y() * v2.Z() - v1.Z() * v2.Y(),
                    v1.Z() * v2.X() - v1.X() * v2.Z(),
                    v1.X() * v2.Y() - v1.Y() * v2.Y());
}

inline bool IsParallel(const Vector3D& v1, const Vector3D& v2) {
    return Cross(v1, v2) == ZeroVector3D;
}

inline bool IsParallel(const Vector2D& v1, const Vector2D& v2) {
    return v1.X() * v2.Y() - v1.Y() * v2.X() == 0;
}

inline bool IsVertical(const Vector3D& v1, const Vector3D& v2) {
    return Dot(v1, v2) == 0;
}

inline bool IsVertical(const Vector2D& v1, const Vector2D& v2) {
    return Dot(v1, v2) == 0;
}

template <typename Vec>
inline Vec Normalize(const Vec& vec) {
    Vec ret(vec);
    ret.Normalize(); // 调用 Vec 的成员函数 Normalize()
    return ret;
}

inline Vector2D operator+(const Vector2D& v1, const Vector2D& v2) {
    return Vector2D(v1.X() + v2.X(), v1.Y() + v2.Y());
}

inline Vector3D operator+(const Vector3D& v1, const Vector3D& v2) {
    return Vector3D(v1.X() + v2.X(), v1.Y() + v2.Y(), v1.Z() + v2.Z());
}

inline Vector4D operator+(const Vector4D& v1, const Vector4D& v2) {
    return Vector4D(v1.X() + v2.X(), v1.Y() + v2.Y(), v1.Z() + v2.Z(), v1.W() + v2.W());
}

inline Vector2D operator-(const Vector2D& v1, const Vector2D& v2) {
    return Vector2D(v1.X() - v2.X(), v1.Y() - v2.Y());
}

inline Vector3D operator-(const Vector3D& v1, const Vector3D& v2) {
    return Vector3D(v1.X() - v2.X(), v1.Y() - v2.Y(), v1.Z() - v2.Z());
}

inline Vector4D operator-(const Vector4D& v1, const Vector4D& v2) {
    return Vector4D(v1.X() - v2.X(), v1.Y() - v2.Y(), v1.Z() - v2.Z(), v1.W() - v2.W());
}

inline Vector2D operator*(const double ratio, const Vector2D& vec) {
    return Vector2D(vec.X() * ratio, vec.Y() * ratio);
}

inline Vector2D operator*(const Vector2D& vec, const double ratio) {
    return Vector2D(vec.X() * ratio, vec.Y() * ratio);
}

inline Vector3D operator*(const double ratio, const Vector3D& vec) {
    return Vector3D(vec.X() * ratio, vec.Y() * ratio, vec.Z() * ratio);
}

inline Vector3D operator*(const Vector3D& vec, const double ratio) {
    return Vector3D(vec.X() * ratio, vec.Y() * ratio, vec.Z() * ratio);
}

inline Vector4D operator*(const double ratio, const Vector4D& vec) {
    return Vector4D(vec.X() * ratio, vec.Y() * ratio, vec.Z() * ratio, vec.W() * ratio);
}

inline Vector4D operator*(const Vector4D& vec, const double ratio) {
    return Vector4D(vec.X() * ratio, vec.Y() * ratio, vec.Z() * ratio, vec.W() * ratio);
}


inline Vector2D Zoom(const double ratio, const Vector2D& vec) {
    return Vector2D(vec.X() * ratio, vec.Y() * ratio);
}

inline Vector2D Zoom(const Vector2D& vec, const double ratio) {
    return Vector2D(vec.X() * ratio, vec.Y() * ratio);
}

inline Vector3D Zoom(const double ratio, const Vector3D& vec) {
    return Vector3D(vec.X() * ratio, vec.Y() * ratio, vec.Z() * ratio);
}

inline Vector3D Zoom(const Vector3D& vec, const double ratio) {
    return Vector3D(vec.X() * ratio, vec.Y() * ratio, vec.Z() * ratio);
}

inline Vector4D Zoom(const double ratio, const Vector4D& vec) {
    return Vector4D(vec.X() * ratio, vec.Y() * ratio, vec.Z() * ratio, vec.W() * ratio);
}

inline Vector4D Zoom(const Vector4D& vec, const double ratio) {
    return Vector4D(vec.X() * ratio, vec.Y() * ratio, vec.Z() * ratio, vec.W() * ratio);
}

template <VectorType Vector>
inline void Clamp(Vector& vec,
                  typename std::remove_cvref_t<Vector>::value_type min,
                  typename std::remove_cvref_t<Vector>::value_type max){
    constexpr size_t N = Vector::Dimension;

    static_for<N>([&](auto i){
        if (vec.coordinates[i] < min){
            vec.coordinates[i] = min;
        }else if (vec.coordinates[i] > max){
            vec.coordinates[i] = max;
        }else{
            // do nothing...
        }
    });
}
template <VectorType Vector>
inline void VectorClamp(Vector& vec, const Vector& min, const Vector& max){
    constexpr size_t N = Vector::Dimension;
    static_for<N>([&](auto i){
        if (vec.coordinates[i] < min.coordinates[i]){
            vec.coordinates[i] = min.coordinates[i];
        }else if (vec.coordinates[i] > max.coordinates[i]){
            vec.coordinates[i] = max.coordinates[i];
        }else{
            // do nothing...
        }
    });
}

};  // namespace ExCCCRender::Core::Math