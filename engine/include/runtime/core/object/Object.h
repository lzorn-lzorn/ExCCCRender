#pragma once
#include "runtime/core/object/Position.h"
namespace ExCCCRender::Core::Object{
/*
 * 该类要接入外部的模型导入工具, 接受导入的模型数据
 */
class Ray;
class HitRecord{};
class Object{
public:

    virtual bool IsHit(const Ray& ray, HitRecord& hit_record) const{
        return false;
    }
public:
    // * 是否需要开启渲染
    bool bShouldRendering = true;
    // * 是否需要开启碰撞
    bool bShouldCollision = true;
private:
    // * 物体位于世界坐标系的坐标位置
    Position position;
    int32_t id{-1};
};

class ObjectGroup{};

}