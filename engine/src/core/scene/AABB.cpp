#include "core/scene/AABB.h"
#include "tools/static_for.hpp"
namespace ExCCCRender::Scene {
    // ! AABBRange ==========================
    bool AABBRange::IsHit(const Ray& ray, double min_time, double max_time) const {
        static_for<3>([&](size_t i, auto breaker){
            auto inv_dir_i = 1.0 / ray.direction[i];
            auto a = (min[i] - ray.origin[i]) * inv_dir_i;
            auto b = (max[i] - ray.origin[i]) * inv_dir_i;
            if(inv_dir_i < 0.0f){
                std::swap(a, b);
            }
            min_time = std::max(min_time, a);
            max_time = std::min(max_time, b);
            if(max_time < min_time){
                breaker.static_break();
            }
        });
        return (max_time >= min_time);
    }

    // ! AABB ==============================
    void AABB::_fill_areas(){

    }


    // ! function ==============================
    AABB MergeBox(AABB box1, AABB box2){
        Point3D small(
            fmin(box1.Min().X(), box2.Min().X()),
            fmin(box1.Min().Y(), box2.Min().Y()),
            fmin(box1.Min().Z(), box2.Min().Z())
        );
        Point3D big(
            fmax(box1.Max().X(), box2.Max().X()),
            fmax(box1.Max().Y(), box2.Max().Y()),
            fmax(box1.Max().Z(), box2.Max().Z())
        );
        return AABB(small, big);
    }
}