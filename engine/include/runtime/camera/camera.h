#pragma once

#include "runtime/core/illumination/Point.h"
namespace ExCCCRender::Core{
using namespace ExCCCRender::Core::Illumination;
class Camera{

public:
    Camera() = default;
    ~Camera() = default;

    Camera(const Camera&) = default;
    Camera& operator=(const Camera&) = default;

    Camera(Camera&&) = default;
    Camera& operator=(Camera&&) = default;

public:


private:
    // * 相机视锥的起点
    Point3D origin; // 等价于 lookfrom
    // * 相机视锥的终点
    Point3D lookat;
    // * 相机的左下角坐标
    Point3D lower_left_corner;
    // * 相机的水平向量 和 垂直向量
    Vector3D horizontal, vertical;
    // * 视口平面的三个坐标系
    Vector3D u, v, w;
    // * 相机的上方向
    Vector3D up;
    // * 镜头半径
    double lens_radius;
    // * 快门开启的时间 和 结束的时间
    double shutter_open, shutter_close;
    // * 光圈大小
    double aperture;
    // * 相机焦距
    double focal_distance;



};

}
