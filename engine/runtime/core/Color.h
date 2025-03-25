#include <cstdint>
#include <../../tools/Vector.hpp>
namespace ExCCCRender::Core {
    struct RGB{
    public:
        using inner_type = uint8_t;
    public:
        explicit RGB(const inner_type& r, const inner_type& g, const inner_type& b):
            vec3d(r, b, g){}
        RGB():vec3d(0,0,0){}
        RGB(const RGB&) = default;
        RGB(RGB&&) = default;
        RGB(const Vector3D<inner_type> vec3d): vec3d(vec3d){}
        RGB& operator=(const RGB&) = default;
        RGB& operator=(RGB&&) = default;
    public:
        Vector3D<inner_type> ToVector3D() const {
            return this->vec3d;
        }
        inner_type GetR() const noexcept{
            return vec3d.GetX();
        }
        inner_type GetG() const noexcept{
            return vec3d.GetY();
        }
        inner_type GetB() const noexcept{
            return vec3d.GetZ();
        }
        RGB& SetR(const inner_type r) noexcept{
            this->vec3d.SetX(r);
            return *this;
        }
        RGB& SetG(const inner_type g) noexcept{
            this->vec3d.SetY(g);
            return *this;
        }
        RGB& SetB(const inner_type b) noexcept{
            this->vec3d.SetZ(b);
            return *this;
        }
        void SetRGB(const inner_type r, const inner_type g, const inner_type b){
            this->vec3d.SetXYZ(r, g, b);
        }
        inner_type R() const noexcept{
            return vec3d.GetX();
        }
        inner_type G() const noexcept{
            return vec3d.GetY();
        }
        inner_type B() const noexcept{
            return vec3d.GetZ();
        }
    public:
        template <typename OtherTy>
        auto Dot(const Vector3D<OtherTy>& other) const -> std::common_type_t<inner_type, OtherTy>{
            return vec3d.Dot(other);
        }

    private:
        Vector3D<inner_type> vec3d{0,0,0};
    };
}