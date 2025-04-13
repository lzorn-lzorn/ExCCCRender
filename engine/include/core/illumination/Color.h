#include <algorithm>
#include <cstdint>
#include "core/math/vector/Vector.hpp"
#include "core/math/vector/VectorDetail.hpp"

namespace ExCCCRender::Core::Illumination {
using namespace ExCCCRender::Core::Math::detail;
struct RGB : public VectorBase<uint8_t, 3> {
public:
    using value_type = uint8_t;
    constexpr static size_t Dimension = 3;

public:
    explicit RGB(const uint8_t r, const uint8_t g, const uint8_t b) : VectorBase<uint8_t, 3>(0, 0, 0) {
    }

    explicit RGB() : VectorBase<uint8_t, 3>(0, 0, 0) {
    }

    ~RGB() = default;
    RGB(const RGB& vec)            = default;
    RGB(RGB&& vec)                 = default;
    RGB& operator=(const RGB& vec) = default;
    RGB& operator=(RGB&& vec)      = default;

    bool operator==(const RGB& color) const {
        return VectorBase<uint8_t, 3>::operator==(color);
    }
    RGB& operator+=(const uint8_t bais){
        for (size_t i=0; i<3; i++){
            int32_t ans = coordinates[i] + bais;
            ans = std::clamp(ans, 0, 255);
            coordinates[i] = ans;
        }
        return *this;
    }
    RGB& operator-=(const uint8_t bais){
        for (size_t i=0; i<3; i++){
            int32_t ans = coordinates[i] - bais;
            ans = std::clamp(ans, 0, 255);
            coordinates[i] = ans;
        }
        return *this;
    }

public:
    uint8_t R() const {
        return coordinates[0];
    }
    uint8_t G() const {
        return coordinates[1];
    }
    uint8_t B() const {
        return coordinates[2];
    }

    RGB& SetR(const uint8_t r) {
        return coordinates[0] = r, *this;
    }
    RGB& SetG(const uint8_t g) {
        return coordinates[1] = g, *this;
    }
    RGB& SetB(const uint8_t b) {
        return coordinates[2] = b, *this;
    }
    RGB& SetRG(const uint8_t r, const uint8_t g){
        coordinates[0] = r;
        coordinates[1] = g;
        return *this;
    }
    RGB& SetRB(const uint8_t r, const uint8_t b){
        coordinates[0] = r;
        coordinates[2] = b;
        return *this;
    }
    RGB& SetGB(const uint8_t g, const uint8_t b){
        coordinates[1] = g;
        coordinates[2] = b;
        return *this;
    }
    RGB& SetRGB(const uint8_t r, const uint8_t g, const uint8_t b) {
        coordinates[0] = r;
        coordinates[1] = g;
        coordinates[2] = b;
        return *this;
    }
    RGB& SetRGB(const RGB& color) {
        coordinates[0] = color.R();
        coordinates[1] = color.G();
        coordinates[2] = color.B();
        return *this;
    }

};
}  // namespace ExCCCRender::Core